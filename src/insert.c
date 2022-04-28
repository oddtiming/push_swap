/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:21:15 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/27 23:40:09 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	insert_b(t_main_cont *cont, t_deque *moves_buff)
{
	t_insert_info	*info;

	if (cont->stack_b.size <= 0)
		return ;
	info = ft_xalloc(sizeof(t_insert_info));
	info->b_info.pos = 0;
	info->min_cost = 1000;
	info->min_delta_insert = 1000;
	while (info->b_info.pos < cont->stack_b.size)
	{
		update_insert_info(cont, info);
		if (info->b_info.pos > info->min_cost
			&& info->b_info.pos <= cont->stack_b.size - info->min_cost
			&& cont->stack_a.size + cont->stack_b.size >= 500)
			info->b_info.pos = cont->stack_b.size - info->min_cost;
		info->b_info.pos++;
	}
	insert_elem_b(cont, moves_buff, info);
	free(info);
	insert_b(cont, moves_buff);
	return ;
}

static void	insert_same_sign(
	t_main_cont *cont, t_deque *moves_buff, t_insert_info *info)
{
	if (info->a_info.dist0_best > 0 || info->b_info.dist0_best > 0)
	{
		while (info->min_cost-- > 0)
		{
			if (--info->a_info.dist0_best < 0)
				do_rb(cont, moves_buff);
			else if (--info->b_info.dist0_best < 0)
				do_ra(cont, moves_buff);
			else
				do_rr(cont, moves_buff);
		}
	}
	else
	{
		while (info->min_cost-- > 0)
		{
			if (++info->a_info.dist0_best > 0)
				do_rrb(cont, moves_buff);
			else if (++info->b_info.dist0_best > 0)
				do_rra(cont, moves_buff);
			else
				do_rrr(cont, moves_buff);
		}
	}
}

static void	insert_same_direction(
	t_main_cont *cont, t_deque *moves_buff, t_insert_info *info)
{
	if (info->min_cost == info->a_info.pos_best
		|| info->min_cost == info->b_info.pos_best)
	{
		while (info->min_cost-- > 0)
		{
			if (--info->a_info.pos_best < 0)
				do_rb(cont, moves_buff);
			else if (--info->b_info.pos_best < 0)
				do_ra(cont, moves_buff);
			else
				do_rr(cont, moves_buff);
		}
	}
	else
	{
		while (info->min_cost-- > 0)
		{
			if (++info->a_info.revpos_best > 0)
				do_rrb(cont, moves_buff);
			else if (++info->b_info.revpos_best > 0)
				do_rra(cont, moves_buff);
			else
				do_rrr(cont, moves_buff);
		}
	}
}

static void	insert_indep_directions(
	t_main_cont *cont, t_deque *moves_buff, t_insert_info *info)
{
	if (info->a_info.dist0_best >= 0)
		while (info->a_info.dist0_best-- > 0)
			do_ra(cont, moves_buff);
	else
		while (info->a_info.dist0_best++ < 0)
			do_rra(cont, moves_buff);
	if (info->b_info.dist0_best >= 0)
		while (info->b_info.dist0_best-- > 0)
			do_rb(cont, moves_buff);
	else
		while (info->b_info.dist0_best++ < 0)
			do_rrb(cont, moves_buff);
}

void	insert_elem_b(
	t_main_cont *cont, t_deque *moves_buff, t_insert_info *info)
{
	t_stack_insert_info	*a_info;
	t_stack_insert_info	*b_info;

	if (cont->stack_b.size <= 0)
		return ;
	a_info = &info->a_info;
	b_info = &info->b_info;
	if (ft_same_sign(a_info->dist0_best, b_info->dist0_best))
		insert_same_sign(cont, moves_buff, info);
	else if (get_cost_either_direction(info) < get_cost_indep_directions(info))
		insert_same_direction(cont, moves_buff, info);
	else
		insert_indep_directions(cont, moves_buff, info);
	do_pa(cont, moves_buff);
	return ;
}
