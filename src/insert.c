#include "push_swap.h"


/**
 * @brief 
 * 
 * For now insert_b does not need a temp_moves_list, b/c it directly
 * inserts the value with lowest insert cost. If two values have the same
 * insert cost (absolute distance from 0), 
 * the one closest in value to its corresponding insert_val,
 * OR closest in value to value at end of stack in dest_stack will be selected.
 * 
 * A potential avenue of optimization would be to calculate in advance if
 * inserting suboptimal curr_pos can result in better overall result. 
 * 	- Would need a linked list for that one, the one in the libft would work!
 * 
 * 
 */

// insert b should do that and exactly that; insert b. 
void	insert_b(t_main_cont *cont, t_deque *moves_buff)
{
	t_insert_info *info;

	if (cont->stack_b.size <= 0)
		return ;
	
	//NEW
	info = malloc(sizeof(t_insert_info));
	if (!info)
		exit_on_err("insert_b: insert_info error\n");

	// if (DEBUG)
	// {
	// 	printf(CYAN"Entered insert_b with %d elements in b \n"RESET_COL, cont->stack_b.size);
	// 	print_stacks(cont);
	// }

	// if b is not empty, init will also call update_insert_info()
	init_insert_info(cont, info);

	while (++info->b_info.pos < cont->stack_b.size)
	{
		// Attempt to not try EVERY value, but only those that can result in fewer moves
		// if stack_b pos is already further than min_moves, set pos to stack_b.size - min_cost
		if (info->b_info.pos > info->min_cost && \
			 info->b_info.pos <= cont->stack_b.size - info->min_cost)
			info->b_info.pos = cont->stack_b.size - info->min_cost;

		update_insert_info(cont, info);
	}
	// if (DEBUG)
	// {
	// 	printf(YELLOW"insert_b found best elem to be stack_b[%d] == %d\n"RESET_COL, info->b_info.pos_best, cont->stack_b.elems[info->b_info.pos_best]);
	// 	printf(YELLOW"corresponding insert value was stack_a[%d] == %d\n"RESET_COL, info->a_info.pos_best, cont->stack_a.elems[info->a_info.pos_best]);
	// 	printf(YELLOW"info.a_info.val_best = %d \n"RESET_COL, info->a_info.val_best);
	// 	printf(YELLOW"info.a_info.pos_best = %d \n"RESET_COL, info->a_info.pos_best);
	// 	printf(YELLOW"info.a_info.revpos_best = %d \n"RESET_COL, info->a_info.revpos_best);
	// 	printf(YELLOW"info.b_info.val_best = %d \n"RESET_COL, info->b_info.val_best);
	// 	printf(YELLOW"info.b_info.pos_best = %d \n"RESET_COL, info->b_info.pos_best);
	// 	printf(YELLOW"info.b_info.revpos_best = %d \n"RESET_COL, info->b_info.revpos_best);
	// 	printf(YELLOW"info.a_info.dist0_best = %d \n"RESET_COL, info->a_info.dist0_best);
	// 	printf(YELLOW"info.b_info.dist0_best = %d \n"RESET_COL, info->b_info.dist0_best);
	// 	printf(YELLOW"info.min_cost = %d \n"RESET_COL, info->min_cost);
	// 	printf(YELLOW"info.min_delta_insert = %d \n"RESET_COL, info->min_delta_insert);
	// }


	if (cont->stack_b.size > 0)
	{
		//TO REMOVE
		// if (info.min_cost < 0)
		if (DEBUG && cont->stack_a.elems[0] > cont->stack_a.elems[1])
		{
			printf("wtf happened here?!? \n");
			print_stacks(cont);
		}
		//EOREMOVE
		
		insert_elem_b(cont, moves_buff, info);

		// if (DEBUG)
		// {
		// 	printf(BLUE"last 5 moves: \n"RESET_COL);
		// 	for (int i = 5; i && moves_buff->size > 5 - i; i--)
		// 		print_move(moves_buff->elems[moves_buff->size - i]);
		// }

		//NEW
		free(info);
		info = NULL;

		if (DEBUG && !is_sorted(&cont->stack_a, cont->head_a.index))
		{
			printf("fucked up right here\n");
			print_stacks(cont);
			printf(BLUE"last 35 moves: \n"RESET_COL);
			for (int i = 35; i && moves_buff->size > 35 - i; i--)
				print_move(moves_buff->elems[moves_buff->size - i]);
			exit(1);
		}

		insert_b(cont, moves_buff);
	}

	//NEW
	free(info);
	info = NULL;
	return ;
}

//NEXT_BIGGER SHOULD CALCULATE IN BOTH DIRECTIONS


// Calculates the minimum number of moves to rotate insert_pos in both to 0.
// If both stacks have the most efficient rotations in the same sense, 
//		return the biggest of the two.
// Else, check if most efficient to rotate indepently or in same direction.
// 
int	calc_insert_cost(t_insert_info *info)
{
	t_stack_insert_info	*b_info;
	t_stack_insert_info	*a_info;
	int 				curr_cost;

	b_info = &info->b_info;
	a_info = &info->a_info;
		
	a_info->dist0 = a_info->pos;
	if (ft_abs(a_info->revpos) < a_info->pos)
		a_info->dist0 = a_info->revpos;

	b_info->dist0 = b_info->pos;
	if (ft_abs(b_info->revpos) < b_info->pos)
		b_info->dist0 = b_info->revpos;

	//If equal in both directions, pick the one in the same direction as the other

	if (ft_abs(a_info->revpos) == a_info->pos && b_info->dist0 < 0)
		a_info->dist0 = a_info->revpos;
	if (ft_abs(b_info->revpos) == b_info->pos && a_info->dist0 < 0)
		b_info->dist0 = b_info->revpos;
	
	curr_cost = ft_max(ft_abs(a_info->dist0), ft_abs(b_info->dist0));
	if (ft_same_sign(a_info->dist0, b_info->dist0))
		return (ft_abs(curr_cost));
	curr_cost = ft_abs(ft_min(ft_max(a_info->pos, b_info->pos), ft_max(-a_info->revpos, -b_info->revpos)));
	curr_cost = ft_abs(ft_min(curr_cost, ft_abs(a_info->dist0) + ft_abs(b_info->dist0)));
	return (curr_cost);
}

void	insert_elem_b(t_main_cont *cont, t_deque *moves_buff, t_insert_info *info)
{
	t_stack_insert_info	*a_info;
	t_stack_insert_info	*b_info;

	if (cont->stack_b.size <= 0)
		return ;
	a_info = &info->a_info;
	b_info = &info->b_info;
	if (cont->stack_b.size > 0)
	{
		//TO REMOVE
		// if (info.min_cost < 0)
		if (DEBUG && (info->min_cost < 0 || \
			(cont->stack_a.elems[0] > cont->stack_a.elems[1] && \
			cont->stack_a.elems[1] != cont->stack_a.min_elem)))
		{
			printf("wtf happened after\n");
			print_stacks(cont);
			printf(YELLOW"info.a_info.val_best = %d \n"RESET_COL, info->a_info.val_best);
			printf(YELLOW"info.a_info.pos_best = %d \n"RESET_COL, info->a_info.pos_best);
			printf(YELLOW"info.a_info.revpos_best = %d \n"RESET_COL, info->a_info.revpos_best);
			printf(YELLOW"info.b_info.val_best = %d \n"RESET_COL, info->b_info.val_best);
			printf(YELLOW"info.b_info.pos_best = %d \n"RESET_COL, info->b_info.pos_best);
			printf(YELLOW"info.b_info.revpos_best = %d \n"RESET_COL, info->b_info.revpos_best);
			printf(YELLOW"info.a_info.dist0_best = %d \n"RESET_COL, info->a_info.dist0_best);
			printf(YELLOW"info.b_info.dist0_best = %d \n"RESET_COL, info->b_info.dist0_best);
			printf(YELLOW"info.min_cost = %d \n"RESET_COL, info->min_cost);
			printf(YELLOW"info.min_delta_insert = %d \n"RESET_COL, info->min_delta_insert);
		}
		//EOREMOVE
	}
	// case for they both need to go in the same sense
	if (ft_same_sign(a_info->dist0_best, b_info->dist0_best))
	{

		if (DEBUG)
		{
			printf(MAGENTA"\t ---> picked same_sign\n"RESET_COL);
		}
		if (a_info->dist0_best > 0 || b_info->dist0_best > 0)
		{
			while (info->min_cost-- > 0)
			{
				a_info->dist0_best--;
				b_info->dist0_best--;
				if (a_info->dist0_best < 0)
					do_rb(cont, moves_buff);
				else if (b_info->dist0_best < 0)
					do_ra(cont, moves_buff);
				else
					do_rr(cont, moves_buff);
			}
			do_pa(cont, moves_buff);
		}
		else
		{
			while (info->min_cost-- > 0)
			{
				a_info->dist0_best++;
				b_info->dist0_best++;
				if (a_info->dist0_best > 0)
					do_rrb(cont, moves_buff);
				else if (b_info->dist0_best > 0)
					do_rra(cont, moves_buff);
				else
					do_rrr(cont, moves_buff);
			}
			do_pa(cont, moves_buff);
		}
		return ;
	}
	// case where their respective best rotations are in opposite directions,
	// but it's still better to move them in same direction
	else if (ft_min(ft_max(a_info->pos_best, b_info->pos_best), ft_max(-a_info->revpos, -b_info->revpos)) < ft_abs(a_info->dist0_best) + ft_abs(b_info->dist0_best) )
	{
		if (DEBUG)
		{
			printf(CYAN"\t ---> picked the weird one\n"RESET_COL);
		}
		if (info->min_cost == a_info->pos_best || info->min_cost == b_info->pos_best)
		{
			while (info->min_cost-- > 0)
			{
				a_info->pos_best--;
				b_info->pos_best--;
				if (a_info->pos_best < 0)
					do_rb(cont, moves_buff);
				else if (b_info->pos_best < 0)
					do_ra(cont, moves_buff);
				else
					do_rr(cont, moves_buff);
			}
			do_pa(cont, moves_buff);
		}
		else
		{
			while (info->min_cost-- > 0)
			{
				a_info->revpos_best++;
				b_info->revpos_best++;
				if (a_info->revpos_best > 0)
					do_rrb(cont, moves_buff);
				else if (b_info->revpos_best > 0)
					do_rra(cont, moves_buff);
				else
					do_rrr(cont, moves_buff);
			}
			do_pa(cont, moves_buff);
		}
		return ;
	}
	// case where they each do their own thing. that's okay too.
	else
	{
		if (DEBUG)
		{
			printf(RED"\t ---> picked independent strong woman\n"RESET_COL);
		}
		if (a_info->dist0_best >= 0)
			while (a_info->dist0_best-- > 0)
				do_ra(cont, moves_buff);
		else
			while (a_info->dist0_best++ < 0)
				do_rra(cont, moves_buff);
		if (b_info->dist0_best >= 0)
			while (b_info->dist0_best-- > 0)
				do_rb(cont, moves_buff);
		else
			while (b_info->dist0_best++ < 0)
				do_rrb(cont, moves_buff);
		do_pa(cont, moves_buff);
	}
	return ;	
}

void	init_insert_info(t_main_cont *cont, t_insert_info *info)
{
	info->b_info.pos = 0;
	info->min_cost = 1000;
	info->min_delta_insert = 1000;

	if (cont->stack_b.size > 0)
		update_insert_info(cont, info);
	return ;
}

/*
 * Calculating delta inserts:
 *		delta insert = ft_max(
 * 						stack_dest[insert_pos] - stack_src[pos], 
 *						stack_src[pos] - stack_dest[insert_pos - 1])
 *
 * Could be done with an iterator.
 * 
 * Not sure if truly beneficial, but I think it is, because I think it 
 * increases the order of the stack by having close values together.
 * I'm going on a feeling for a sorting algorithm, lol.
 * 
 */	

// Conditions: 

int	calc_delta_two_values(t_main_cont *cont, int val_a, int val_b)
{
	int	delta_insert;
	int	max_a;
	int	min_a; 
	int	max_b; 
	int	min_b;

	max_a = cont->stack_a.max_elem;
	min_a = cont->stack_a.min_elem;
	max_b = cont->stack_b.max_elem;
	min_b = cont->stack_b.min_elem;
	delta_insert = ft_abs(val_a - val_b); // is now equal to the diff between the two
	//if bigger than half the absolute diff
	if (delta_insert <= (ft_max(max_a, max_b) + 1) / 2)
		return (delta_insert);
	delta_insert = (max_a - val_a) + (val_b - min_b) + 1;
	if (val_b > val_a)
		delta_insert = (max_b - val_b) + (val_a - min_a) + 1;
	return (delta_insert);
}

//Need to add absolute distance from previous one
int	calc_delta_insert(t_main_cont *cont, t_insert_info *info)
{
	t_iterator	*iter;
	int			delta_insert;

	iter = malloc(sizeof(t_iterator));
	if (!iter)
		exit_on_err("calc_delta_insert: iter error\n");
	set_iterator(iter, info->a_info.pos, cont->stack_a.size, 1);
	iterate_once(iter, 1);
	delta_insert = calc_delta_two_values(cont, cont->stack_a.elems[iter->index], cont->stack_b.elems[iter->index]);
	delta_insert = ft_min(delta_insert, \
		calc_delta_two_values(cont, info->a_info.val, info->b_info.val));
	free(iter);
	return (delta_insert);
}

bool	is_new_best_moves(t_insert_info *info)
{
	if (info->curr_cost > info->min_cost)
		return (false);
	if (info->curr_cost == info->min_cost)
	{
		if (info->curr_delta_insert > info->min_delta_insert)
			return (false);
		if (info->curr_delta_insert == info->min_delta_insert && \
				info->b_info.val > info->b_info.val_best) //Not sure about that last part
			return (true);
	}
	return (true);
}


void	update_insert_info(t_main_cont *cont, t_insert_info *info)
{
	t_stack_insert_info *a_info;
	t_stack_insert_info *b_info;

	a_info = &info->a_info;
	b_info = &info->b_info;
	b_info->revpos = b_info->pos - cont->stack_b.size;
	b_info->val = cont->stack_b.elems[b_info->pos];
	a_info->val = get_next_value(&cont->stack_a, b_info->val);
	a_info->pos = get_pos_of_val(&cont->stack_a, a_info->val);
	a_info->revpos = a_info->pos - cont->stack_a.size;
	//Will calculate the minimum distance between two points in two stacks
	info->curr_cost = calc_insert_cost(info);
	//curr_delta_cost needs to also take into account delta with last elem in stack_a
	info->curr_delta_insert = calc_delta_insert(cont, info);
	// if ((info->curr_cost == info->min_cost && \
	// 	info->curr_delta_insert < info->min_delta_insert)\
	// 	|| info->curr_cost < info->min_cost)
	// if ((info->curr_cost == info->min_cost && \
		// b_info->val > b_info->val_best)\
		// || info->curr_cost < info->min_cost)
	if (is_new_best_moves(info))
	{
		b_info->val_best = b_info->val;
		b_info->pos_best = b_info->pos;
		b_info->revpos_best = b_info->revpos;
		b_info->dist0_best = b_info->dist0;
		a_info->val_best = a_info->val;
		a_info->pos_best = a_info->pos;
		a_info->revpos_best = a_info->revpos;
		a_info->dist0_best = a_info->dist0;
		info->min_cost = info->curr_cost;
		info->min_delta_insert = info->curr_delta_insert;
	}
	return ;
}

//Need to add condition where delta cost and min cost are equal, pick one with highetst value