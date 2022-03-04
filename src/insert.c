#include "push_swap.h"


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

// insert b should do that and exactly that; insert b. 
void	insert_b(t_main_cont *cont, t_deque *moves_buff)
{
	t_insert_info info;

	if (cont->stack_b.size <= 0)
		return ;
	if (DEBUG)
	{
		printf(CYAN"Entered insert_b\n"RESET_COL);
		print_stacks_info(cont);
	}

	// if b is not empty, will also call update_insert_info()
	init_insert_info(cont, &info);
	while (++info.b_info.pos < cont->stack_b.size)
	{
		// Attempt to not try EVERY value, but only those that can result in fewer moves
		// if stack_b pos is already further than min_moves, set pos to stack_b.size - min_cost
		if (info.b_info.pos > info.min_cost && \
			 info.b_info.pos < cont->stack_b.size - info.min_cost)
			info.b_info.pos = cont->stack_b.size - info.min_cost;
		update_insert_info(cont, &info);
	}
	if (DEBUG)
	{
		printf(YELLOW"insert_b found best elem to be stack_b[%d] == %d\n"RESET_COL, info.b_info.pos_best, cont->stack_b.elems[info.b_info.pos_best]);
		printf(YELLOW"corresponding insert value was stack_a[%d] == %d\n"RESET_COL, info.a_info.pos_best, cont->stack_a.elems[info.a_info.pos_best]);
	}
	if (cont->stack_b.size > 0)
	{
		insert_elem_b(cont, moves_buff, &info);
		insert_b(cont, moves_buff);
	}
	if (DEBUG)
	{
		printf(CYAN"After insert_b\n"RESET_COL);
	}
	return ;
}


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
		
	b_info->dist0 = b_info->pos;
	if (ft_abs(b_info->revpos) < b_info->pos)
		b_info->dist0 = b_info->revpos;

	a_info->dist0 = a_info->pos;
	if (ft_abs(a_info->revpos) < a_info->pos)
		a_info->dist0 = a_info->revpos;
	//If equal in both directions, pick the one in the same direction as the other

	if ((ft_abs(b_info->revpos) == b_info->pos && \
			a_info->dist0 < 0))
		b_info->dist0 = b_info->revpos;
	if ((ft_abs(a_info->revpos) == a_info->pos && \
			b_info->dist0 < 0))
		a_info->dist0 = a_info->revpos;
	
	curr_cost = ft_max(ft_abs(a_info->dist0), ft_abs(b_info->dist0));
	if (ft_same_sign(a_info->dist0, b_info->dist0))
		return (curr_cost);
	else
		curr_cost = ft_min(ft_max(a_info->pos, b_info->pos), ft_max(-a_info->revpos, -b_info->revpos));
	curr_cost = ft_min(curr_cost, ft_abs(a_info->dist0) + ft_abs(b_info->dist0));
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
	// case for they both need to go in the same sense
	if (ft_same_sign(a_info->dist0_best, b_info->dist0_best))
	{
		if (a_info->dist0_best > 0)
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
		if (ft_max(a_info->pos_best, b_info->pos_best) < ft_max(-a_info->revpos, -b_info->revpos))
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
				if (a_info->revpos_best >= 0)
					do_rrb(cont, moves_buff);
				else if (b_info->revpos_best >= 0)
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
	info->min_cost = INT_MAX - 1;
	info->min_delta_insert = INT_MAX - 1;

	if (cont->stack_b.size > 0)
		update_insert_info(cont, info);
	return ;
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
	info->curr_delta_insert = ft_abs(a_info->val - b_info->val);
	if ((info->curr_cost == info->min_cost && \
		info->curr_delta_insert < info->min_delta_insert)\
		|| info->curr_cost < info->min_cost)
	{
		info->min_delta_insert = info->curr_delta_insert;
		info->min_cost = info->curr_cost;
		b_info->val_best = b_info->val;
		b_info->pos_best = b_info->pos;
		b_info->revpos_best = b_info->revpos;
		b_info->dist0_best = b_info->dist0;
		a_info->val_best = a_info->val;
		a_info->pos_best = a_info->pos;
		a_info->revpos_best = a_info->revpos;
		a_info->dist0_best = a_info->dist0;
	}
	return ;
}
