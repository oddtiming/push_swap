/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_in_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:34:20 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/05/01 21:39:34 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	try_single_cutoff(
	t_main_cont *cont, t_deque *block_ids, float cutoff)
{
	partition_leaving_vals_cutoff(
		&cont->leaving_vals,
		block_ids,
		(int)(max_elem_leaving(cont, &cont->leaving_vals) * cutoff));
	insert_block_of_a_in_b(cont, block_ids, 0);
	insert_block_of_a_in_b(cont, block_ids, 1);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
		copy_deque(&cont->curr_moves, &cont->best_moves);
	copy_deque(&cont->initial_stack, &cont->stack_a);
	deque_reinit_list(&cont->stack_b);
	deque_reinit_list(&cont->curr_moves);
	return ;
}

static void	try_multiple_cutoffs_body(
	t_main_cont *cont, t_deque *block_ids, float cutoff, int id_to_push)
{
	int	i;

	partition_leaving_vals_cutoff(
		&cont->leaving_vals,
		block_ids,
		(int)(max_elem_leaving(cont, &cont->leaving_vals) * cutoff));
	insert_block_of_a_in_b(cont, block_ids, id_to_push);
	deque_reinit_list(&cont->leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(&cont->staying_vals, cont->stack_a.elems[i]))
			cont->leaving_vals.add_last(&cont->leaving_vals, -1);
		else
			cont->leaving_vals.add_last(
				&cont->leaving_vals,
				cont->stack_a.elems[i]);
		i++;
	}
}

static void	try_multiple_cutoffs_footer(
	t_main_cont *cont, t_deque *block_ids, float cutoff, int id_to_push)
{
	int	i;

	partition_leaving_vals_cutoff(
		&cont->leaving_vals, block_ids,
		(int)(max_elem_leaving(cont, &cont->leaving_vals) * cutoff));
	insert_block_of_a_in_b(cont, block_ids, id_to_push);
	insert_block_of_a_in_b(cont, block_ids, (id_to_push + 1) % 2);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
		copy_deque(&cont->curr_moves, &cont->best_moves);
	copy_deque(&cont->initial_stack, &cont->stack_a);
	deque_reinit_list(&cont->stack_b);
	deque_reinit_list(&cont->curr_moves);
	deque_reinit_list(&cont->leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(&cont->staying_vals, cont->stack_a.elems[i]))
			cont->leaving_vals.add_last(&cont->leaving_vals, -1);
		else
			cont->leaving_vals.add_last(
				&cont->leaving_vals, cont->stack_a.elems[i]);
		i++;
	}	
}

void	split_in_two_mult_cutoffs(t_main_cont *cont, t_deque *block_ids)
{
	try_multiple_cutoffs_body(cont, block_ids, 0.6F, 1);
	try_multiple_cutoffs_body(cont, block_ids, 0.5F, 1);
	try_multiple_cutoffs_body(cont, block_ids, 0.5F, 1);
	try_multiple_cutoffs_footer(cont, block_ids, 0.4F, 1);
	try_multiple_cutoffs_body(cont, block_ids, 0.6F, 1);
	try_multiple_cutoffs_body(cont, block_ids, 0.5F, 1);
	try_multiple_cutoffs_footer(cont, block_ids, 0.4F, 1);
	try_multiple_cutoffs_body(cont, block_ids, 0.6F, 1);
	try_multiple_cutoffs_footer(cont, block_ids, 0.4F, 1);
	try_multiple_cutoffs_body(cont, block_ids, 0.6F, 1);
	try_multiple_cutoffs_body(cont, block_ids, 0.5F, 1);
	try_multiple_cutoffs_body(cont, block_ids, 0.5F, 1);
	try_multiple_cutoffs_footer(cont, block_ids, 0.4F, 0);
	try_multiple_cutoffs_body(cont, block_ids, 0.6F, 1);
	try_multiple_cutoffs_body(cont, block_ids, 0.5F, 1);
	try_multiple_cutoffs_footer(cont, block_ids, 0.4F, 0);
	try_multiple_cutoffs_body(cont, block_ids, 0.6F, 1);
	try_multiple_cutoffs_footer(cont, block_ids, 0.4F, 0);
	try_multiple_cutoffs_body(cont, block_ids, 0.5F, 1);
	try_multiple_cutoffs_body(cont, block_ids, 0.5F, 1);
	try_multiple_cutoffs_footer(cont, block_ids, 0.5F, 1);
	try_multiple_cutoffs_body(cont, block_ids, 0.5F, 0);
	try_multiple_cutoffs_body(cont, block_ids, 0.5F, 0);
	try_multiple_cutoffs_footer(cont, block_ids, 0.5F, 0);
}

void	split_in_two(t_main_cont *cont)
{
	t_deque	*block_ids;

	new_deque(&block_ids);
	try_single_cutoff(cont, block_ids, 5 / 8);
	try_single_cutoff(cont, block_ids, 13 / 24);
	try_single_cutoff(cont, block_ids, 11 / 24);
	try_single_cutoff(cont, block_ids, 3 / 8);
	try_single_cutoff(cont, block_ids, 7 / 24);
	split_in_two_mult_cutoffs(cont, block_ids);
	block_ids->free_list(block_ids);
	free(block_ids);
	return ;
}
