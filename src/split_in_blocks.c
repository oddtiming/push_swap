/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_blocks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:04:01 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 22:04:19 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	split_in_n_blocks(
	t_main_cont *cont, t_deque *block_ids_a, t_deque *block_ids_b, int n)
{
	int		i;

	partition_leaving_vals_n_blocks(&cont->leaving_vals, block_ids_a, n);
	i = n;
	while (--i >= 0)
		insert_block_set_ids(cont, block_ids_a, block_ids_b, i);
	i = 0;
	while (i < n)
	{
		insert_block_of_b_in_a(cont, block_ids_b, i);
		i++;
	}
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	copy_deque(&cont->initial_stack, &cont->stack_a);
	deque_reinit_list(&cont->stack_b);
	deque_reinit_list(&cont->curr_moves);
	deque_reinit_list(block_ids_b);
	return ;
}

void	split_in_blocks(t_main_cont *cont)
{
	t_deque	*block_ids_a;
	t_deque	*block_ids_b;
	int		nb_blocks;

	new_deque(&block_ids_a);
	new_deque(&block_ids_b);
	nb_blocks = 2;
	while (nb_blocks <= 6)
	{
		split_in_n_blocks(cont, block_ids_a, block_ids_b, nb_blocks);
		nb_blocks++;
	}
	block_ids_a->free_list(block_ids_a);
	free(block_ids_a);
	block_ids_b->free_list(block_ids_b);
	free(block_ids_b);
	return ;
}
