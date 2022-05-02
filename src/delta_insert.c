<<<<<<< HEAD
=======
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

>>>>>>> aae4d5e87735a81400d9797777a9c7de4307c7e5
#include "push_swap.h"

int	calc_delta_two_values(t_main_cont *cont, int val_a, int val_b)
{
	int	delta_insert;
	int	max_a;
<<<<<<< HEAD
	int	min_a; 
	int	max_b; 
=======
	int	min_a;
	int	max_b;
>>>>>>> aae4d5e87735a81400d9797777a9c7de4307c7e5
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

<<<<<<< HEAD
//Need to add absolute distance from previous one
int	calc_delta_insert(t_main_cont *cont, t_insert_info *info)
{
	t_iterator	*iter;
	int			delta_insert;

	iter = malloc(sizeof(t_iterator));
	if (!iter)
		exit_on_err("calc_delta_insert: iter error\n");
	set_iterator(iter, info->a_info.pos, cont->stack_a.size, 1);
	iterate_once(iter, 1);
	delta_insert = calc_delta_two_values(
			cont,
			cont->stack_a.elems[iter->index],
			cont->stack_b.elems[iter->index]);
	delta_insert = ft_min(delta_insert, \
		calc_delta_two_values(cont, info->a_info.val, info->b_info.val));
	free(iter);
	return (delta_insert);
=======
int	calc_delta_insert(t_main_cont *cont, t_insert_info *info)
{
	return (calc_delta_two_values(cont, info->a_info.val, info->b_info.val));
>>>>>>> aae4d5e87735a81400d9797777a9c7de4307c7e5
}
