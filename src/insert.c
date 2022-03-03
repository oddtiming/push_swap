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
void	insert_b(t_main_cont *cont, t_deque *temp_moves)
{
	t_insert_info info;

	if (cont->stack_b.size <= 0)
		return ;
	if (DEBUG)
	{
		printf(CYAN"Entered insert_b\n"RESET_COL);
		print_stacks_info(cont);
	}
	// if (cont->stack_b.size == 0)
	// {
	// 	rotate_to_0_in_a(cont, temp_moves, cont->head_a.index);
	// 	return ;
	// }
	init_insert_info(&info);
	info.b_info.pos = 0;

	while (cont->stack_b.size > 0 && info.b_info.pos < cont->stack_b.size)
	{
		// Attempt to not try EVERY value, but only those that can result in better results
		// if it's reached too far and is smaller than half, reset to next_end - min_cost
		if (cont->stack_b.size - info.b_info.pos > info.min_cost && \
			cont->stack_b.size - info.min_cost < info.b_info.pos)
			info.b_info.pos = cont->stack_b.size - info.min_cost;
		update_insert_info(cont, &info);
		info.b_info.pos++;
	}
	if (DEBUG)
	{
		printf(YELLOW"insert_b found best elem to be stack_b[%d] == %d\n"RESET_COL, info.b_info.pos_best, cont->stack_b.elems[info.b_info.pos_best]);
		printf(YELLOW"corresponding insert value was stack_a[%d] == %d\n"RESET_COL, info.a_info.pos_best, cont->stack_a.elems[info.a_info.pos_best]);
	}
	if (cont->stack_b.size > 0)
	{
		insert_elem_b(cont, temp_moves, &info);
		insert_b(cont, temp_moves);
	}
	if (DEBUG)
	{
		printf(CYAN"After insert_b\n"RESET_COL);
	}
	return ;
}


// This fct calculates the minimum number of moves to rotate both pos to 0.
// If both stacks have the most efficient rotations in the same sense, return.
// Else, check if most efficient to rotate indepently or in same direction.
int	calculate_insert_cost(t_insert_info *info)
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
	//this is hella redundant, but at least it hopefully does what it needs to do
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
			while (info->min_cost-- > 0)
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
			while (info->min_cost-- > 0)
			{
				a_info->pos_best--;
				b_info->pos_best--;
				if (a_info->pos_best < 0)
					do_rb(cont, temp_moves);
				else if (b_info->pos_best < 0)
					do_ra(cont, temp_moves);
				else
					do_rr(cont, temp_moves);
			}
			do_pa(cont, temp_moves);
		}
		else
		{
			while (info->min_cost-- > 0)
			{
				a_info->revpos_best++;
				b_info->revpos_best++;
				if (a_info->revpos_best >= 0)
					do_rrb(cont, temp_moves);
				else if (b_info->revpos_best >= 0)
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
			while (a_info->dist0_best-- > 0)
				do_ra(cont, temp_moves);
		else
			while (a_info->dist0_best++ < 0)
				do_rra(cont, temp_moves);
		if (b_info->dist0_best >= 0)
			while (b_info->dist0_best-- > 0)
				do_rb(cont, temp_moves);
		else
			while (b_info->dist0_best++ < 0)
				do_rrb(cont, temp_moves);
		do_pa(cont, temp_moves);
	}
	return ;	
}

void	init_insert_info(t_insert_info *info)
{
	info->min_cost = INT_MAX;
	info->min_delta_insert = INT_MAX;
}

void	update_insert_info(t_main_cont *cont, t_insert_info *info)
{
	t_stack_insert_info *a_info;
	t_stack_insert_info *b_info;

	a_info = &info->a_info;
	b_info = &info->b_info;
	b_info->revpos = b_info->pos - cont->stack_b.size;
	b_info->val = cont->stack_b.elems[b_info->pos];
	a_info->val = get_next_bigger(&cont->stack_a, b_info->val);
	a_info->pos = get_pos_of_val(&cont->stack_a, a_info->val);
	a_info->revpos = a_info->pos - cont->stack_a.size;
	//Will calculate the minimum distance between two points in two stacks
	info->curr_cost = calculate_insert_cost(info);
	//curr_delta_cost needs to also take into account delta with last elem in a
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
		b_info->dist0_best = INT_MAX;
		a_info->val_best = a_info->val;
		a_info->pos_best = a_info->pos;
		a_info->revpos_best = a_info->revpos;
	}
}
