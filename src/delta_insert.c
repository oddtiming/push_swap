/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:21:52 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/05/01 21:11:59 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	calc_delta_two_values(t_main_cont *cont, int val_a, int val_b)
{
	int	delta_insert;
	int	max_a;
	int	min_a;
	int	max_b;
	int	min_b;

	max_a = cont->stack_a.max_elem;
	min_a = cont->stack_a.min_elem;
	max_b = cont->stack_b.max_elem;
	min_b = cont->stack_b.min_elem;
	delta_insert = ft_abs(val_a - val_b);
	if (delta_insert <= (ft_max(max_a, max_b) + 1) / 2)
		return (delta_insert);
	delta_insert = (max_a - val_a) + (val_b - min_b) + 1;
	if (val_b > val_a)
		delta_insert = (max_b - val_b) + (val_a - min_a) + 1;
	return (delta_insert);
}

int	calc_delta_insert(t_main_cont *cont, t_insert_info *info)
{
	return (calc_delta_two_values(cont, info->a_info.val, info->b_info.val));
}
