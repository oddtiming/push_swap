/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:54:39 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 22:03:01 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	block_id_is_in_stack(t_deque *block_ids, int id)
{
	int	i;

	i = 0;
	while (i < block_ids->size)
	{
		if (block_ids->elems[i] == id)
			return (true);
		i++;
	}
	return (false);
}

void	assign_block_median(
	t_deque *stack, t_deque *block_ids, t_block_info *info)
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
		while (pos_a && cont->stack_b.elems[0] > info->median_val
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
