/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:05:43 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 22:05:43 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_cost_either_direction(t_insert_info *info)
{
	return (ft_min(
			ft_max(info->a_info.pos_best, info->b_info.pos_best),
			ft_max(-info->a_info.revpos, -info->b_info.revpos)));
}

int	get_cost_indep_directions(t_insert_info *info)
{
	return (ft_abs(info->a_info.dist0_best) + ft_abs(info->b_info.dist0_best));
}

// Will return the next bigger value in the index, or stack_x.min_elem
int	get_insert_val(t_deque *stack, int curr_val)
{
	int	pos;
	int	next_bigger;

	if (curr_val + 1 > stack->max_elem)
		return (stack->min_elem);
	next_bigger = curr_val + 1;
	pos = 0;
	while (pos < stack->size)
	{
		if (stack->elems[pos] == next_bigger)
			return (next_bigger);
		pos++;
	}
	return (get_insert_val(stack, curr_val + 1));
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
