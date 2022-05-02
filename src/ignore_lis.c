/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore_LIS.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:36:17 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/05/01 21:36:46 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	ignore_lis2(t_main_cont *cont, t_deque *block_ids)
{
	int	i;

	i = -1;
	while (++i < 7)
		try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 10 / 24);
	i = -1;
	while (++i < 7)
		try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 11 / 24);
	i = -1;
	while (++i < 7)
		try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 13 / 24);
	i = -1;
	while (++i < 7)
		try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 14 / 24);
	i = -1;
	while (++i < 7)
		try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 15 / 24);
	i = -1;
	while (++i < 7)
		try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 16 / 24);
	i = -1;
	while (++i < 7)
		try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 17 / 24);
}

void	ignore_lis(t_main_cont *cont)
{
	t_deque	*block_ids;
	int		i;

	new_deque(&block_ids);
	i = -1;
	while (++i < 7)
		try_n_divisions_smallest(cont, block_ids, i);
	i = -1;
	while (++i < 7)
		try_n_divisions_closest(cont, block_ids, i);
	i = -1;
	while (++i < 7)
		try_n_divisions(cont, block_ids, i);
	i = -1;
	while (++i < 7)
		try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 7 / 24);
	i = -1;
	while (++i < 7)
		try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 8 / 24);
	i = -1;
	while (++i < 7)
		try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 9 / 24);
	ignore_lis2(cont, block_ids);
	block_ids->free_list(block_ids);
	free(block_ids);
}
