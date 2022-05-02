/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_blocks_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:18:58 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/27 23:39:27 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void	insert_block_of_b_in_a(
	t_main_cont *cont, t_deque *block_ids_b, int block_id)
{
	t_insert_info	*info;

	if (!block_id_is_in_stack(block_ids_b, block_id))
		return ;
	info = ft_xalloc(sizeof(t_insert_info));
	info->min_cost = INT_MAX;
	info->min_delta_insert = INT_MAX;
	info->b_info.pos = 0;
	while (info->b_info.pos < block_ids_b->size)
	{
		if (block_ids_b->elems[info->b_info.pos] == block_id)
			update_insert_info(cont, info);
		info->b_info.pos++;
	}
	if (cont->stack_b.size > 0)
	{
		insert_block_elem_b(cont, block_ids_b, info);
		insert_block_of_b_in_a(cont, block_ids_b, block_id);
	}
	free(info);
	info = NULL;
	return ;
}

void	insert_curr_block_id(
	t_main_cont *cont,
	t_deque *block_ids_a,
	t_deque *block_ids_b,
	t_block_info *info)
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
