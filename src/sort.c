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
int	calculate_abs_min_dist(t_main_cont *cont, int pos_a, int pos_b)
{
	int revpos_a;
	int dist_a;
	int revpos_b;
	int dist_b;
	int	dist_tot;

	if (pos_a < 0 || pos_b < 0)
		return (INT_MAX);
	revpos_a = pos_a - cont->stack_a.nb_elems;
	dist_a = pos_a;
	if (ft_abs(revpos_a) < pos_a)
		dist_a = revpos_a;
	revpos_b = pos_b - cont->stack_b.nb_elems;
	dist_b = pos_b;
	if (ft_abs(revpos_b) < pos_b)
		dist_b = revpos_b;
	dist_tot = ft_max(ft_abs(dist_a), ft_abs(dist_b));
	if (ft_same_sign(dist_a, dist_b))
		return (dist_tot);
	else
		dist_tot = ft_min(ft_max(pos_a, pos_b), ft_max(-revpos_a, -revpos_b));
	dist_tot = ft_min(dist_tot, ft_abs(dist_a) + ft_abs(dist_b));
	return (dist_tot);
}

void	insert_elem_b(t_main_cont *cont, int pos_a, int pos_b)
{
	int revpos_a;
	int dist_a;
	int revpos_b;
	int dist_b;
	int	dist_tot;

	revpos_a = pos_a - cont->stack_a.nb_elems;
	dist_a = pos_a;
	if (ft_abs(revpos_a) < pos_a)
		dist_a = revpos_a;
	revpos_b = pos_b - cont->stack_b.nb_elems;
	dist_b = pos_b;
	// if both equal, pick the one in the same direction
	if (ft_abs(revpos_b) < pos_b || (ft_abs(revpos_b) == pos_b && dist_a < 0))
		dist_b = revpos_b;
	dist_tot = ft_max(ft_abs(dist_a), ft_abs(dist_b));
	// case for they both need to go in the same sense
	if (ft_same_sign(dist_a, dist_b))
	{
		if (dist_a > 0)
		{
			while (dist_tot--)
			{
				dist_a--;
				dist_b--;
				if (dist_a < 0)
					do_rb(cont, &cont->temp_moves);
				else if (dist_b < 0)
					do_ra(cont, &cont->temp_moves);
				else
					do_rr(cont, &cont->temp_moves);
			}
			do_pa(cont, &cont->temp_moves);
		}
		else
		{
			while (dist_tot--)
			{
				dist_a++;
				dist_b++;
				if (dist_a > 0)
					do_rrb(cont, &cont->temp_moves);
				else if (dist_b > 0)
					do_rra(cont, &cont->temp_moves);
				else
					do_rrr(cont, &cont->temp_moves);
			}
			do_pa(cont, &cont->temp_moves);
		}
		return ;
	}
	// case where their respective best rotations are in opposite directions,
	// but it's still better to move them in same direction
	else if (ft_min(ft_max(pos_a, pos_b), ft_max(-revpos_a, -revpos_b)) < ft_abs(dist_a) + ft_abs(dist_b) )
	{
		if (ft_max(pos_a, pos_b) < ft_max(-revpos_a, -revpos_b))
		{
			while (dist_tot--)
			{
				dist_a--;
				dist_b--;
				if (dist_a < 0)
					do_rb(cont, &cont->temp_moves);
				else if (dist_b < 0)
					do_ra(cont, &cont->temp_moves);
				else
					do_rr(cont, &cont->temp_moves);
			}
			do_pa(cont, &cont->temp_moves);
		}
		else
		{
			while (dist_tot--)
			{
				dist_a++;
				dist_b++;
				if (dist_a > 0)
					do_rrb(cont, &cont->temp_moves);
				else if (dist_b > 0)
					do_rra(cont, &cont->temp_moves);
				else
					do_rrr(cont, &cont->temp_moves);
			}
			do_pa(cont, &cont->temp_moves);
		}
		return ;
	}
	// case where they each do their own thing. that's okay too.
	else
	{
		if (dist_a >= 0)
			while (dist_a--)
				do_ra(cont, &cont->temp_moves);
		else
			while (dist_a++)
				do_rra(cont, &cont->temp_moves);
		if (dist_b >= 0)
			while (dist_b--)
				do_rb(cont, &cont->temp_moves);
		else
			while (dist_b++)
				do_rrb(cont, &cont->temp_moves);
	}
	return ;	
}

//Here's the logic for insert_b:
//	Should be recursive and take a temp_moves as a parameter;
//	for each iteration, the fct should:
//		- keep in store the positions for the N smallest nb_moves to insert
//		- Iterate through these N values to compare the outcomes recursively can be.
//		- undo the last_move if the 
//	at the end, the list with the smallest nb_moves is concatenated to cont's temp_moves
//
// FOR NOW, though, simply calculate which element is fastest to insert, mb recursively
void	insert_b(t_main_cont *cont)
{
	int	best_pos_in_a;
	int	best_pos_in_b;
	int	curr_pos_in_b;
	int	curr_pos_in_a;
	int	curr_insert_value_in_a;
	int	curr_insert_value_in_b;
	int	curr_cost;
	int	min_cost;
	
	min_cost = INT_MAX;
	curr_pos_in_b = 0;
	best_pos_in_a = 0;
	best_pos_in_b = 0;
	while (curr_pos_in_b < cont->stack_b.nb_elems)
	{

		// Attempt to not try EVERY value, but only those that can result in better results
		// if it's reached too far and is smaller than half, reset to next_end - min_cost
		if (curr_pos_in_b > min_cost && cont->stack_b.nb_elems - curr_pos_in_b > curr_pos_in_b)
			curr_pos_in_b = cont->stack_b.nb_elems - min_cost;

// maybe just switch to straight up recursively inserting all other elements.
// would need a temp_stack that exists outside of this fct.
//---> temp_stack could be a member of main_cont.
// Need to remove some unnecessary complexity

		curr_insert_value_in_b = cont->stack_b.elems[curr_pos_in_b];
		curr_insert_value_in_a = get_next_bigger(&cont->stack_a, curr_insert_value_in_b);
		//Will calculate the minimum distance between two points in two stacks
		curr_pos_in_a = get_pos_of_val(&cont->stack_a, curr_insert_value_in_a);
		curr_cost = calculate_abs_min_dist(cont, curr_pos_in_a, curr_pos_in_b);
		if (curr_cost < min_cost)
		{
			min_cost = curr_cost;
			best_pos_in_b = curr_pos_in_b;
			best_pos_in_a = curr_pos_in_a;
		}
		curr_pos_in_b++;
	}
	if (DEBUG)
	{
		printf(YELLOW"insert_b found best elem to be stack_b[%d] == %d\n"RESET_COL, best_pos_in_b, cont->stack_b.elems[best_pos_in_b]);
		printf(YELLOW"corresponding insert value was stack_a[%d] == %d\n"RESET_COL, best_pos_in_a, cont->stack_a.elems[best_pos_in_a]);
	}
	insert_elem_b(cont, best_pos_in_a, best_pos_in_b);
	if (cont->stack_b.nb_elems)
		insert_b(cont);
	rotate_to_0_in_a(cont, &cont->temp_moves, cont->head_a.index);
}

bool	invert_4(t_main_cont *cont)
{
	do_sa(cont, &cont->temp_moves);
	do_ra(cont, &cont->temp_moves);
	do_ra(cont, &cont->temp_moves);
	do_sa(cont, &cont->temp_moves);
	insert_b(cont);
	if (is_sorted(&cont->stack_a, cont->head_a.index))
	{
		if (DEBUG)
		{
			printf(CYAN"\t stack is sorted\n"RESET_COL);
			print_stacks_info(cont);
		}
		return (true);
	}
	undo_moves(cont, &cont->temp_moves);
	return (false);
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
			cat_deque(temp_moves_list, &cont->temp_moves);
			temp_moves_list->free_list(temp_moves_list);
			free(temp_moves_list);
			return (true);
		}
		undo_moves(cont, temp_moves_list);
		i++;
	}
	temp_moves_list->free_list(temp_moves_list);
	free(temp_moves_list);
	return (false);
}

void	compare_moves(t_main_cont *cont)
{
	insert_b(cont);
	if (DEBUG && !is_sorted(&cont->stack_a, cont->head_a)
	{
		print_stacks_info(cont);
		exit_on_err("dat look sorted to you?\n");
	}
	if (cont->temp_moves.nb_elems < )
	{
		min_moves = cont->temp_moves.nb_elems;
		copy_deque(&cont->temp_moves, &temp_moves);				
	}
	undo_moves(cont, &cont->temp_moves);
}

void	try_pb(t_main_cont *cont)
{
	int		i;
	int		min_moves;

	min_moves = INT_MAX;
	i = 0;
	while (i < cont->stack_a.nb_elems)
	{
		if (is_sorted(&cont->stack_a, cont->head_a.index) || try_swap(cont))
		{

		}
		rotate_to_0_in_a(cont, &cont->temp_moves, i);
		do_pb(cont, &cont->temp_moves);
		if (try_swap(cont))
		{
			min_moves = cont->temp_moves.nb_elems;
			copy_deque(&cont->temp_moves, &temp_moves);
		}

		if (invert_4(cont))
		{
			if (cont->temp_moves.nb_elems < min_moves)
			{
				min_moves = cont->temp_moves.nb_elems;
				copy_deque(&cont->temp_moves, &temp_moves);
			}

		}
		undo_moves(cont, &cont->temp_moves);
		rotate_to_0_in_a(cont, &cont->temp_moves, i);
		do_pb(cont, &cont->temp_moves);
		do_pb(cont, &cont->temp_moves);
		if (!is_sorted(&cont->stack_a, cont->head_a.index))
			do_sa(cont, &cont->temp_moves);
		insert_b(cont);
		if (cont->temp_moves.nb_elems < min_moves)
		{
			min_moves = cont->temp_moves.nb_elems;
			copy_deque(&cont->temp_moves, &temp_moves);
		}
		undo_moves(cont, &cont->temp_moves);
		i++;
	}
	copy_deque(&temp_moves, &cont->temp_moves);
	return ;
}

void	sort_small(t_main_cont *cont)
{
	if (is_sorted(&cont->stack_a, cont->head_a.index) || try_swap(cont))
	{
		rotate_to_0_in_a(cont, &cont->temp_moves, cont->head_a.index);
		return ;
	}
	try_pb(cont);
	return ;
}

void	sort(t_main_cont *cont)
{
	if (cont->stack_a.nb_elems < 10)
		sort_small(cont);
	return ;
}