#include "push_swap.h"

bool	block_id_is_in_stack(t_deque *block_ids, int id)
{
	int	i;

	i = 0;
	while (i < block_ids->size)
	{
		if(block_ids->elems[i] == id)
			return (true);
		i++;
	}
	return (false);
}

void	assign_block_median(t_deque *stack, t_deque *block_ids, t_block_info *info)
{
	int	curr_pos;

	info->median_val = 0;
	curr_pos = 0;
	while (curr_pos < stack->size)
	{
		if (block_ids->elems[curr_pos] == info->curr_block_id)
		{
			if (stack->elems[curr_pos] < info->min_val)
				info->min_val = stack->elems[curr_pos];
			else if (stack->elems[curr_pos] > info->max_val)
				info->max_val = stack->elems[curr_pos];
		}
		curr_pos++;
	}
	info->median_val = (info->max_val - info->min_val) / 2 + info->min_val;
	return ;
}

bool	has_smaller_than_median(t_deque *stack, t_block_info *info)
{
	int	curr_pos;

	curr_pos = 0;
	while (curr_pos < stack->size)
	{
		if (stack->elems[curr_pos] >= info->min_val
			&& stack->elems[curr_pos] <= info->median_val)
			return (true);
		curr_pos++;
	}
	return (false);
}

void	rotate_block_split(
	t_main_cont *cont, t_deque *block_ids, t_block_info *info)
{
	int	pos_a;

	pos_a = 0;
	while (block_ids->elems[pos_a] != info->curr_block_id)
		pos_a++;
	if (has_smaller_than_median(&cont->stack_b, info))
	{
		while (pos_a
			&& cont->stack_b.elems[0] > info->median_val
			&& cont->stack_b.elems[0] <= info->max_val)
		{
			do_rr(cont, &cont->curr_moves);
			block_ids->add_last(block_ids, block_ids->elems[0]);
			block_ids->remove_front(block_ids);
			pos_a--;
		}
	}
	while (pos_a)
	{
		do_ra(cont, &cont->curr_moves);
		block_ids->add_last(block_ids, block_ids->elems[0]);
		block_ids->remove_front(block_ids);
		pos_a--;
	}
	return ;
}

void	insert_block_of_a_in_b(
	t_main_cont *cont, t_deque *block_ids, int curr_block_id)
{
	t_block_info	info;

	info.curr_block_id = curr_block_id;
	info.max_val = 0;
	info.min_val = cont->stack_a.max_elem;
	assign_block_median(&cont->stack_a, block_ids, &info);
	while (block_id_is_in_stack(block_ids, curr_block_id))
	{
		if (block_ids->elems[0] == curr_block_id)
		{
			while (has_smaller_than_median(&cont->stack_b, &info)
					&& cont->stack_a.elems[0] <= info.median_val
					&& cont->stack_b.elems[0] > info.median_val 
					&& cont->stack_b.elems[0] <= info.max_val)
				do_rb(cont, &cont->curr_moves);
			do_pb(cont, &cont->curr_moves);
			block_ids->remove_front(block_ids);
		}
		else
			rotate_block_split(cont, block_ids, &info);
	}
	while (cont->stack_b.elems[0] > info.median_val
		&& cont->stack_b.elems[0] <= info.max_val)
		do_rb(cont, &cont->curr_moves);
	return ;
}

void	sort_big(t_main_cont *cont)
{
	int	initial_size;

	initial_size = cont->stack_a.size;
	insert_b(cont, &cont->best_moves);
	rotate_to_0_in_a(cont, &cont->best_moves, cont->head_a.index);
}

void	insert_last_block(t_main_cont *cont, t_deque *moves_list)
{
	t_block_info	info;

	info.max_val = cont->stack_a.max_elem;
	info.min_val = cont->stack_a.min_elem;
	info.median_val = (info.max_val - info.min_val) / 2;
	while (cont->stack_a.size > 3)
	{
		do_pb(cont, &cont->curr_moves);
		if (has_smaller_than_median(&cont->stack_b, &info)
			&& cont->stack_b.elems[0] > info.median_val
			&& cont->stack_b.elems[0] <= info.max_val)
			do_rb(cont, moves_list);
	}
	if (!is_sorted(&cont->stack_a, cont->head_a.index))
		do_sa(cont, moves_list);
	return ;
}
