/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_block_elems.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:02:10 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 18:02:21 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	insert_block_elem_rot(
	t_main_cont *cont, t_deque *block_ids_b, t_insert_info *info)
{
	while (info->min_cost-- > 0)
	{
		if (--info->b_info.pos_best < 0)
			do_ra(cont, &cont->curr_moves);
		else
		{
			if (--info->a_info.pos_best < 0)
				do_rb(cont, &cont->curr_moves);
			else
				do_rr(cont, &cont->curr_moves);
			block_ids_b->add_last(block_ids_b, block_ids_b->elems[0]);
			block_ids_b->remove_front(block_ids_b);
		}
	}
	do_pa(cont, &cont->curr_moves);
	block_ids_b->remove_front(block_ids_b);
}

static void	insert_block_elem_revrot(
	t_main_cont *cont, t_deque *block_ids_b, t_insert_info *info)
{
	while (info->min_cost-- > 0)
	{
		if (++info->b_info.revpos_best > 0)
			do_rra(cont, &cont->curr_moves);
		else
		{
			if (++info->a_info.revpos_best > 0)
				do_rrb(cont, &cont->curr_moves);
			else
				do_rrr(cont, &cont->curr_moves);
			block_ids_b->add_front(block_ids_b,
				block_ids_b->elems[block_ids_b->size - 1]);
			block_ids_b->remove_last(block_ids_b);
		}
	}
	do_pa(cont, &cont->curr_moves);
	block_ids_b->remove_front(block_ids_b);
}

static void	insert_indep_directions(
	t_main_cont *cont, t_deque *block_ids_b, t_insert_info *info)
{
	if (info->a_info.dist0_best >= 0)
		while (info->a_info.dist0_best-- > 0)
			do_ra(cont, &cont->curr_moves);
	else
		while (info->a_info.dist0_best++ < 0)
			do_rra(cont, &cont->curr_moves);
	if (info->b_info.dist0_best >= 0)
	{
		while (info->b_info.dist0_best-- > 0)
		{
			do_rb(cont, &cont->curr_moves);
			block_ids_b->add_last(block_ids_b, block_ids_b->elems[0]);
			block_ids_b->remove_front(block_ids_b);
		}
	}
	while (info->b_info.dist0_best++ < 0)
	{
		do_rrb(cont, &cont->curr_moves);
		block_ids_b->add_front(block_ids_b,
			block_ids_b->elems[block_ids_b->size - 1]);
		block_ids_b->remove_last(block_ids_b);
	}
	do_pa(cont, &cont->curr_moves);
	block_ids_b->remove_front(block_ids_b);
}

void	insert_block_elem_b(
	t_main_cont *cont, t_deque *block_ids_b, t_insert_info *info)
{
	if (cont->stack_b.size <= 0)
		return ;
	if (ft_same_sign(info->a_info.dist0_best, info->b_info.dist0_best))
	{
		if (info->a_info.dist0_best > 0 || info->b_info.dist0_best > 0)
			insert_block_elem_rot(cont, block_ids_b, info);
		else
			insert_block_elem_revrot(cont, block_ids_b, info);
	}
	else if (get_cost_either_direction(info) < get_cost_indep_directions(info))
	{
		if (info->min_cost == info->a_info.pos_best
			|| info->min_cost == info->b_info.pos_best)
			insert_block_elem_rot(cont, block_ids_b, info);
		else
			insert_block_elem_revrot(cont, block_ids_b, info);
	}
	else
		insert_indep_directions(cont, block_ids_b, info);
	return ;
}
