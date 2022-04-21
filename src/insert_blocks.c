/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_blocks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 17:41:52 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 17:43:30 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	insert_curr_block_id(
	t_main_cont *cont,
	t_deque *block_ids_a,
	t_deque *block_ids_b,
	t_block_info	*info)
{
	while (cont->stack_a.elems[0] <= info->median_val
		&& has_smaller_than_median(&cont->stack_b, info)
		&& cont->stack_b.elems[0] > info->median_val
		&& cont->stack_b.elems[0] <= info->max_val)
	{
		do_rb(cont, &cont->curr_moves);
		block_ids_b->add_last(block_ids_b, block_ids_b->elems[0]);
		block_ids_b->remove_front(block_ids_b);
	}
	do_pb(cont, &cont->curr_moves);
	if (cont->stack_b.elems[0] >= info->median_val)
		block_ids_b->add_front(block_ids_b, 1);
	else
		block_ids_b->add_front(block_ids_b, 0);
	block_ids_a->remove_front(block_ids_a);
}

void	rotate_to_block_id(
	t_main_cont *cont,
	t_deque *block_ids_a,
	t_deque *block_ids_b,
	t_block_info	*info)
{
	int	pos_a;

	pos_a = 0;
	while (block_ids_a->elems[pos_a] != info->curr_block_id)
		pos_a++;
	if (has_smaller_than_median(&cont->stack_b, info))
	{
		while (pos_a && cont->stack_b.elems[0] > info->median_val
			&& cont->stack_b.elems[0] <= info->max_val)
		{
			do_rr(cont, &cont->curr_moves);
			block_ids_b->add_last(block_ids_b, block_ids_b->elems[0]);
			block_ids_b->remove_front(block_ids_b);
			block_ids_a->add_last(block_ids_a, block_ids_a->elems[0]);
			block_ids_a->remove_front(block_ids_a);
			pos_a--;
		}
	}
	while (pos_a)
	{
		do_ra(cont, &cont->curr_moves);
		block_ids_a->add_last(block_ids_a, block_ids_a->elems[0]);
		block_ids_a->remove_front(block_ids_a);
		pos_a--;
	}
}

void	check_if_top_stack_b_is_smaller_than_median(
	t_main_cont *cont, t_deque *block_ids, t_block_info *info)
{
	while (cont->stack_b.elems[0] > info->median_val
		&& cont->stack_b.elems[0] <= info->max_val)
	{
		do_rb(cont, &cont->curr_moves);
		block_ids->add_last(block_ids, block_ids->elems[0]);
		block_ids->remove_front(block_ids);
	}
	return ;
}

void	insert_block_set_ids(
	t_main_cont *cont,
	t_deque *block_ids_a,
	t_deque *block_ids_b,
	int curr_block_id_a)
{
	t_block_info	info;
	int				i;

	info.curr_block_id = curr_block_id_a;
	info.max_val = 0;
	info.min_val = cont->stack_a.max_elem;
	assign_block_median(&cont->stack_a, block_ids_a, &info);
	i = 0;
	while (i < block_ids_b->size)
	{
		block_ids_b->elems[i] += 2;
		i++;
	}
	while (block_id_is_in_stack(block_ids_a, curr_block_id_a))
	{
		if (block_ids_a->elems[0] == curr_block_id_a)
			insert_curr_block_id(cont, block_ids_a, block_ids_b, &info);
		else
			rotate_to_block_id(cont, block_ids_a, block_ids_b, &info);
	}
	check_if_top_stack_b_is_smaller_than_median(cont, block_ids_b, &info);
	return ;
}
