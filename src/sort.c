#include "push_swap.h"

int ft_max(int a, int b)
{
	return ((a >= b) * a + (b > a) * b);
}

int ft_min(int a, int b)
{
	return ((a <= b) * a + (b < a) * b);
}

int ft_abs(int a)
{
	return ((a >= 0) * a + (a < 0) * (-a));
}

bool	ft_same_sign(int a, int b)
{
	return ((a >= 0 && b >= 0) || ((a < 0) && (b < 0)));
}

// This fct calculates the minimum number of moves to rotate both pos to 0.
// If both stacks have the most efficient rotations in the same sense, return.
// Else, check if most efficient to rotate indepently or in same direction.
int	calculate_min_cost(t_main_cont *cont, t_insert_info *info)
{
	t_stack_insert_info	*a_info;
	t_stack_insert_info	*b_info;
	int 				curr_cost;

	a_info = &info->a_info;
	b_info = &info->b_info;
	a_info->dist0 = a_info->pos;
	if (ft_abs(a_info->revpos) < a_info->pos)
		a_info->dist0 = a_info->revpos;
	b_info->dist0 = b_info->pos;
	if ((ft_abs(b_info->revpos_best) == b_info->pos_best && \
			a_info->dist0_best < 0) \
			|| ft_abs(b_info->revpos) < b_info->pos)
		b_info->dist0 = b_info->revpos;
	//this is hella redundant, but at least it hopefulyl does what it needs to do
	curr_cost = ft_max(ft_abs(a_info->dist0), ft_abs(b_info->dist0));
	if (ft_same_sign(a_info->dist0, b_info->dist0))
		return (curr_cost);
	else
		curr_cost = ft_min(ft_max(a_info->pos, b_info->pos), ft_max(-a_info->revpos, -b_info->revpos));
	curr_cost = ft_min(curr_cost, ft_abs(a_info->dist0) + ft_abs(b_info->dist0));
	return (curr_cost);
}
void	insert_elem_b(t_main_cont *cont, t_deque *temp_moves, t_insert_info *info)
{
	t_stack_insert_info	*a_info;
	t_stack_insert_info	*b_info;

	a_info = &info->a_info;
	b_info = &info->b_info;
	// case for they both need to go in the same sense
	if (ft_same_sign(a_info->dist0_best, b_info->dist0_best))
	{
		if (a_info->dist0_best > 0)
		{
			while (info->min_cost--)
			{
				a_info->dist0_best--;
				b_info->dist0_best--;
				if (a_info->dist0_best < 0)
					do_rb(cont, temp_moves);
				else if (b_info->dist0_best < 0)
					do_ra(cont, temp_moves);
				else
					do_rr(cont, temp_moves);
			}
			do_pa(cont, temp_moves);
		}
		else
		{
			while (info->min_cost--)
			{
				a_info->dist0_best++;
				b_info->dist0_best++;
				if (a_info->dist0_best > 0)
					do_rrb(cont, temp_moves);
				else if (b_info->dist0_best > 0)
					do_rra(cont, temp_moves);
				else
					do_rrr(cont, temp_moves);
			}
			do_pa(cont, temp_moves);
		}
		return ;
	}
	// case where their respective best rotations are in opposite directions,
	// but it's still better to move them in same direction
	else if (ft_min(ft_max(a_info->pos_best, b_info->pos_best), ft_max(-a_info->revpos, -b_info->revpos)) < ft_abs(a_info->dist0_best) + ft_abs(b_info->dist0_best) )
	{
		if (ft_max(a_info->pos_best, b_info->pos_best) < ft_max(-a_info->revpos, -b_info->revpos))
		{
			while (info->min_cost--)
			{
				a_info->dist0_best--;
				b_info->dist0_best--;
				if (a_info->dist0_best < 0)
					do_rb(cont, temp_moves);
				else if (b_info->dist0_best < 0)
					do_ra(cont, temp_moves);
				else
					do_rr(cont, temp_moves);
			}
			do_pa(cont, temp_moves);
		}
		else
		{
			while (info->min_cost--)
			{
				a_info->dist0_best++;
				b_info->dist0_best++;
				if (a_info->dist0_best > 0)
					do_rrb(cont, temp_moves);
				else if (b_info->dist0_best > 0)
					do_rra(cont, temp_moves);
				else
					do_rrr(cont, temp_moves);
			}
			do_pa(cont, temp_moves);
		}
		return ;
	}
	// case where they each do their own thing. that's okay too.
	else
	{
		if (a_info->dist0_best >= 0)
			while (a_info->dist0_best--)
				do_ra(cont, temp_moves);
		else
			while (a_info->dist0_best++)
				do_rra(cont, temp_moves);
		if (b_info->dist0_best >= 0)
			while (b_info->dist0_best--)
				do_rb(cont, temp_moves);
		else
			while (b_info->dist0_best++)
				do_rrb(cont, temp_moves);
		do_pa(cont, temp_moves);
	}
	return ;	
}

void	init_insert_info(t_main_cont *cont, t_insert_info *insert_info)
{
	insert_info->a_info.dist0 = 0;
	insert_info->a_info.pos = 0;
	insert_info->a_info.revpos = info->a_info.pos - cont->stack_a.nb_elems;
	insert_info->a_info.val = cont->stack_a[0];
	insert_info->a_info.dist0_best = INT_MAX;
	insert_info->a_info.pos_best = 0;
	insert_info->a_info.revpos_best = 0 - cont->stack_a.nb_elems;
	insert_info->a_info.val_best = cont->stack_a[0];

	insert_info->b_info.dist0 = 0;
	insert_info->b_info.pos = 0;
	insert_info->b_info.revpos = info->b_info.pos - cont->stack_b.nb_elems;
	insert_info->b_info.val = cont->stack_b[0];
	insert_info->b_info.dist0_best = INT_MAX;
	insert_info->b_info.pos_best = 0;
	insert_info->b_info.revpos_best = 0 - cont->stack_b.nb_elems;
	insert_info->b_info.val_best = cont->stack_b[0];

	insert_info->best_delta_insert = INT_MAX;
	insert_info->curr_delta_insert = 0;
	insert_info->min_cost = INT_MAX;
	insert_info->min_cost = 0;
}

void	calculate_insert_info(t_main_cont *cont, t_insert_info *info)
{
	t_stack_insert_info *a_info;
	t_stack_insert_info *b_info;

	a_info = &info->a_info;
	b_info = &info->b_info;
	b_info->revpos = b_info->pos - cont->stack_b.nb_elems;
	b_info->val = cont->stack_b.elems[b_info->pos];
	a_info->val = get_next_bigger(&cont->stack_a, b_info->val);
	a_info->pos = get_pos_of_val(&cont->stack_a, a_info->val);
	a_info->revpos = a_info->pos - cont->stack_a.nb_elems;
	//Will calculate the minimum distance between two points in two stacks
	info->curr_cost = calculate_min_cost(cont, info);
	info->curr_delta_insert = ft_abs(a_info->val - b_info->val);
	if ((info->curr_cost == info->min_cost && \
		info->curr_delta_insert < info->best_delta_insert)\
		|| info->curr_cost < info->min_cost)
	{
		info->best_delta_insert = info->curr_delta_insert;
		info->min_cost = info->curr_cost;
		b_info->pos_best = b_info->pos;
		b_info->revpos_best = b_info->revpos;
		a_info->pos_best = a_info->pos;
		a_info->revpos_best = a_info->revpos;
	}
}


/**
 * @brief 
 * 
 * For now insert_b does not need a temp_moves_list, b/c it directly
 * inserts the value with lowest insert cost. If two values have the same
 * insert cost (absolute distance from 0), 
 * the one closest in value to its corresponding insert_val will be selected.
 * 
 * A potential avenue of optimization would be to calculate in advance if
 * inserting suboptimal curr_pos can result in better overall result.
 * 	- Not sure how to test
 * 
 * 
 */
void	insert_b(t_main_cont *cont, t_deque *temp_moves)
{
	static t_insert_info	*info;

	if (!info)
	{
		insert_info = malloc(sizeof(t_insert_info));
		if (!info)
			exit_on_err("insert_b: insert_info malloc error\n");
		init_insert_info(cont, insert_info);
	}
	info->b_info.pos = 0;
	while (info->b_info.pos < cont->stack_b.nb_elems)
	{
		// Attempt to not try EVERY value, but only those that can result in better results
		// if it's reached too far and is smaller than half, reset to next_end - min_cost
		if (info->b_info.pos && cont->stack_b.nb_elems - info->b_info.pos > info->b_info.pos)
			info->b_info.pos = cont->stack_b.nb_elems - min_cost;
		calculate_insert_info(cont, info);
		info->b_info.pos++;
	}
	if (DEBUG)
	{
		printf(YELLOW"insert_b found best elem to be stack_b[%d] == %d\n"RESET_COL, best_pos_in_b, cont->stack_b.elems[best_pos_in_b]);
		printf(YELLOW"corresponding insert value was stack_a[%d] == %d\n"RESET_COL, best_pos_in_a, cont->stack_a.elems[best_pos_in_a]);
	}
	insert_elem_b(cont, temp_moves, info);
	if (cont->stack_b.nb_elems)
		insert_b(cont, temp_moves);
	rotate_to_0_in_a(cont, temp_moves, cont->head_a.index);
	compare_moves(cont, temp_moves);
	free (info);
	return ;
}

void	copy_deque(t_deque *src, t_deque *dest)
{
	int	i;

	dest->reinit_list(dest);
	i = 0;
	while (i < src->nb_elems)
	{
		dest->add_last(dest, src->elems[i]);
		i++;
	}
	return ;
}

void	cat_deque(t_deque *src, t_deque *dest)
{
	int	i;

	i = 0;
	while (i < src->nb_elems)
	{
		dest->add_last(dest, src->elems[i]);
		i++;
	}
	return ;
}

void	cat_deque_front(t_deque *src, t_deque *dest)
{
	int	i;

	i = src->nb_elems - 1;
	while (i >= 0)
	{
		dest->add_front(dest, src->elems[i]);
		i;
	}
	return ;
}

bool	try_invert_4(t_main_cont *cont)
{
	t_deque	*temp_moves_list;

	temp_moves_list = malloc(sizeof(t_deque));
	if (!temp_moves_list)
		return (false);
	init_deque(temp_moves_list);
	do_sa(cont, temp_moves_list);
	do_ra(cont, temp_moves_list);
	do_ra(cont, temp_moves_list);
	do_sa(cont, temp_moves_list);
	if (is_sorted(&cont->stack_a, cont->head_a.index))
	{
		insert_b(cont, temp_moves);
		temp_moves_list->free_list(temp_moves_list);
		free(temp_moves_list);
		temp_moves_list = NULL;
		if (DEBUG)
		{
			printf(CYAN"\t try_invert_4 succedded\n"RESET_COL);
		}
		return (true);
	}
	undo_moves(cont, temp_moves_list);
	temp_moves_list->free_list(temp_moves_list);
	free(temp_moves_list);
	temp_moves_list = NULL;
	return (false);
}

bool	try_swap(t_main_cont *cont)
{
	int		i;
	t_deque	*temp_moves_list;

	temp_moves_list = malloc(sizeof(t_deque));
	if (!temp_moves_list)
		return (false);
	init_deque(temp_moves_list);
	i = 0;
	while (i < cont->stack_a.nb_elems)
	{
		rotate_to_0_in_a(cont, temp_moves_list, i);
		do_sa(cont, temp_moves_list);
		if (is_sorted(&cont->stack_a, cont->head_a.index))
		{
			insert_b(cont, temp_moves);
			temp_moves_list->free_list(temp_moves_list);
			free(temp_moves_list);
			temp_moves_list = NULL;
			if (DEBUG)
			{
				printf(CYAN"\t try_swap succedded\n"RESET_COL);
			}
			return (true);
		}
		undo_moves(cont, temp_moves_list);
		i++;
	}
	temp_moves_list->free_list(temp_moves_list);
	free(temp_moves_list);
	temp_moves_list = NULL;
	return (false);
}

void	compare_moves(t_main_cont *cont, t_deque *temp_moves)
{
	if (!is_sorted(&cont->stack_a, cont->head_a.index))
	{
		if (DEBUG)
		{
			print_stacks_info(cont);
			exit_on_err("dat look sorted to you?\n");
		}
	}
	else if (cont->best_moves.malloced_space == NULL)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
		cat_deque(temp_moves, &cont->best_moves);
	}
	else if (cont->curr_moves.nb_elems + temp_moves->nb_elems < cont->best_moves.nb_elems)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
		cat_deque(temp_moves, &cont->best_moves);
	}
	undo_moves(cont, temp_moves);
}

//to integrate later
void	compare_delta_inserts(t_main_cont *cont)
{
	if (cont->curr_moves.nb_elems == cont->best_moves.nb_elems \
		&& cont->curr_delta_insert < cont->best_delta_insert)
			copy_deque(&cont->curr_moves, &cont->best_moves);		
	return ;
}

//I need some static temp_moves, b/c otherwise the pushes get erased all the time
// Maybe I just need a curr_move_list
// temp_moves_list gets transferred to curr_moves_list once an impass has been reached
// In this case, it would be when it is sorted


/**
 * 	I need all of my moves_list to live exclusively in the context of the try_fct
 * 	I don't want it to affect what happens outside of it, because then I lose track
 * 	of what has been done in which subfunction.
 * 
 * 	compare_moves() should compare if the sum total of local temp and cont->temp
 * 	is smaller than the curr_best_moves, and if so cat them to new curr_best_moves
 * 
 * Technically I don't need delta_inserts, because I'll try pushing every value anyways
 * 
 * 
 * temp_moves:	
 * 		moves that had to be done to the current stack, including 
 * 		but not limited to pushes that have been done and need to be commited 
 * 		before the next recursion takes place.
 * best_moves:
 * 		collection of moves that have the best outcome for the current algorithm.
 * temp_moves_list:
 * 		list of moves that exist only in the context of a specific fct.
 * 		if the fct is "successful", a check will be made with compare_moves to see if
 * 		the temp_moves added to the temp_moves add up to fewer moves than previously
 * 		registered in best_moves
 * final_moves:
 * 		the final list of moves to be printed.
 * 		Assigned from the algo with the fewest resulting moves
 * 
 */


void	try_pb(t_main_cont *cont)
{
	int		i;
	int		min_moves;
	t_deque	*temp_moves_list;		

	temp_moves_list = malloc(sizeof(t_deque));
	if (!temp_moves_list)
		exit_on_err("t_deque malloc oopsie\n");
	init_deque(temp_moves_list);
	min_moves = INT_MAX;
	i = 0;
	while (i < cont->stack_a.nb_elems)
	{
		if (cont->best_moves.nb_elems <= 7 && cont->best_moves.malloced_space)
			return ;
		if (is_sorted(&cont->stack_a, cont->head_a.index))
			insert_b(cont, temp_moves_list);
		if (try_swap(cont))
			insert_b(cont, temp_moves_list);
		else if (cont->stack_a.nb_elems == 4 && try_invert_4(cont))
			insert_b(cont);
		else
		{
			rotate_to_0_in_a(cont, temp_moves_list)
			do_pb(cont, temp_moves_list);
			cat_deque(temp_moves_list, &cont->curr_moves);
			try_pb(cont);
		}
		i++;
	}
	undo_moves(cont, temp_moves_list);
	temp_moves_list->free_list(temp_moves_list);
	free(temp_moves_list);
	temp_moves_list = NULL;
	return ;
}

void	sort_small(t_main_cont *cont)
{
	try_pb(cont);
	copy_deque(&cont->best_moves, &cont->final_moves);
	return ;
}

void	sort(t_main_cont *cont)
{
	if (cont->stack_a.nb_elems < 10)
		sort_small(cont);
	return ;
}