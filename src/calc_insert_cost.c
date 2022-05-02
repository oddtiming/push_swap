/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_insert_cost.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 20:15:47 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/05/01 21:21:29 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	set_best_individual_costs(
		t_stack_insert_info *a_info, t_stack_insert_info *b_info)
{
	a_info->dist0 = a_info->pos;
	if (ft_abs(a_info->revpos) < a_info->pos)
		a_info->dist0 = a_info->revpos;
	b_info->dist0 = b_info->pos;
	if (ft_abs(b_info->revpos) < b_info->pos)
		b_info->dist0 = b_info->revpos;
	if (ft_abs(a_info->revpos) == a_info->pos && b_info->dist0 < 0)
		a_info->dist0 = a_info->revpos;
	if (ft_abs(b_info->revpos) == b_info->pos && a_info->dist0 < 0)
		b_info->dist0 = b_info->revpos;
	return ;
}

static int	get_best_absolute_cost(
		t_stack_insert_info *a_info, t_stack_insert_info *b_info)
{
	int	curr_cost;

	curr_cost = ft_max(ft_abs(a_info->dist0), ft_abs(b_info->dist0));
	if (ft_same_sign(a_info->dist0, b_info->dist0))
		return (ft_abs(curr_cost));
	curr_cost = ft_min(
			ft_max(a_info->pos, b_info->pos),
			ft_max(-a_info->revpos, -b_info->revpos));
	curr_cost = ft_min(
			curr_cost,
			ft_abs(a_info->dist0) + ft_abs(b_info->dist0));
	return (curr_cost);
}

// Calculates the minimum number of moves to rotate insert_pos in both to 0.
// If both stacks have the most efficient rotations in the same sense, 
//		return the biggest of the two.
// Else, check if most efficient to rotate indepently or in same direction.
// 
int	calc_insert_cost(t_insert_info *info)
{
	int	curr_cost;

	set_best_individual_costs(&info->a_info, &info->b_info);
	curr_cost = get_best_absolute_cost(&info->a_info, &info->b_info);
	return (curr_cost);
}

static bool	is_new_best_moves(t_insert_info *info)
{
	if (info->curr_cost > info->min_cost)
		return (false);
	if (info->curr_cost == info->min_cost)
	{
		if (info->curr_delta_insert > info->min_delta_insert)
			return (false);
		if (info->curr_delta_insert == info->min_delta_insert && \
				info->b_info.val > info->b_info.val_best)
			return (true);
	}
	return (true);
}

void	update_insert_info(t_main_cont *cont, t_insert_info *info)
{
	t_stack_insert_info	*a_info;
	t_stack_insert_info	*b_info;

	a_info = &info->a_info;
	b_info = &info->b_info;
	b_info->revpos = b_info->pos - cont->stack_b.size;
	b_info->val = cont->stack_b.elems[b_info->pos];
	a_info->val = get_insert_val(&cont->stack_a, b_info->val);
	a_info->pos = get_pos_of_val(&cont->stack_a, a_info->val);
	a_info->revpos = a_info->pos - cont->stack_a.size;
	info->curr_cost = calc_insert_cost(info);
	info->curr_delta_insert = calc_delta_insert(cont, info);
	if (is_new_best_moves(info))
	{
		b_info->val_best = b_info->val;
		b_info->pos_best = b_info->pos;
		b_info->revpos_best = b_info->revpos;
		b_info->dist0_best = b_info->dist0;
		a_info->val_best = a_info->val;
		a_info->pos_best = a_info->pos;
		a_info->revpos_best = a_info->revpos;
		a_info->dist0_best = a_info->dist0;
		info->min_cost = info->curr_cost;
		info->min_delta_insert = info->curr_delta_insert;
	}
}
