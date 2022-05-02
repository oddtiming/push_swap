/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_blocks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2022/04/20 17:41:52 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 17:43:30 by iyahoui-         ###   ########.fr       */
=======
/*   Created: 2022/04/20 22:28:30 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 22:30:37 by iyahoui-         ###   ########.fr       */
>>>>>>> aae4d5e87735a81400d9797777a9c7de4307c7e5
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

<<<<<<< HEAD
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
=======
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

void	insert_block_rot(
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
	return ;
}

void	insert_block_rev_rot(
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
	return ;
}

void	insert_indep_directions(
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
	else
	{
		while (info->b_info.dist0_best++ < 0)
		{
			do_rrb(cont, &cont->curr_moves);
			block_ids_b->add_front(block_ids_b,
				block_ids_b->elems[block_ids_b->size - 1]);
			block_ids_b->remove_last(block_ids_b);
		}
	}
}

void	insert_block_elem_b(
	t_main_cont *cont, t_deque *block_ids_b, t_insert_info *info)
{
	if (cont->stack_b.size <= 0)
		return ;
	if (ft_same_sign(info->a_info.dist0_best, info->b_info.dist0_best))
	{
		if (info->a_info.dist0_best > 0 || info->b_info.dist0_best > 0)
			insert_block_rot(cont, block_ids_b, info);
		else
			insert_block_rev_rot(cont, block_ids_b, info);
>>>>>>> aae4d5e87735a81400d9797777a9c7de4307c7e5
	}
	else if (get_cost_either_direction(info) < get_cost_indep_directions(info))
	{
		if (info->min_cost == info->a_info.pos_best
			|| info->min_cost == info->b_info.pos_best)
			insert_block_rot(cont, block_ids_b, info);
		else
			insert_block_rev_rot(cont, block_ids_b, info);
	}
	else
		insert_indep_directions(cont, block_ids_b, info);
	do_pa(cont, &cont->curr_moves);
	block_ids_b->remove_front(block_ids_b);
	return ;
}
