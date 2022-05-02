/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore_lis_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:41:19 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 23:41:19 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	complete_algo(t_main_cont *cont)
{
	insert_last_block(cont, &cont->curr_moves);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	copy_deque(&cont->initial_stack, &cont->stack_a);
	deque_reinit_list(&cont->stack_b);
	deque_reinit_list(&cont->curr_moves);
	return ;
}

void	try_cutoff_n(t_main_cont *cont, t_deque *block_ids, int n, int cutoff)
{
	int	i;

	i = 0;
	while (i < n)
	{
		partition_stack_cutoff(&cont->stack_a, block_ids, cutoff);
		insert_block_of_a_in_b(cont, block_ids, 1);
		i++;
	}
	complete_algo(cont);
	return ;
}

void	try_n_divisions(t_main_cont *cont, t_deque *block_ids, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		partition_stack_in_two(&cont->stack_a, block_ids);
		insert_block_of_a_in_b(cont, block_ids, 1);
		i++;
	}
	complete_algo(cont);
	return ;
}

void	try_n_divisions_smallest(t_main_cont *cont, t_deque *block_ids, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		partition_stack_in_two(&cont->stack_a, block_ids);
		insert_block_of_a_in_b(cont, block_ids, 0);
		i++;
	}
	complete_algo(cont);
	return ;
}

void	try_n_divisions_closest(t_main_cont *cont, t_deque *block_ids, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		partition_stack_in_two(&cont->stack_a, block_ids);
		insert_block_of_a_in_b(cont, block_ids, block_ids->elems[0]);
		i++;
	}
	complete_algo(cont);
	return ;
}
