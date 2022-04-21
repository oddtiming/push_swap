/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:26:46 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/21 00:23:35 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(t_deque *stack_src, t_deque *stack_dest)
{
	stack_dest->add_front(stack_dest, stack_src->elems[0]);
	stack_src->remove_front(stack_src);
	return ;
}

static inline void	push_update_iterators(t_main_cont *cont)
{
	set_iterator(
		&cont->head_a,
		get_pos_smallest_val(&cont->stack_a), cont->stack_a.size, 0);
	set_iterator(
		&cont->head_b,
		get_pos_smallest_val(&cont->stack_b), cont->stack_b.size, 1);
	return ;
}

void	do_pa(t_main_cont *cont, t_deque *curr_moves)
{
	push(&cont->stack_b, &cont->stack_a);
	if (curr_moves)
		curr_moves->add_last(curr_moves, PA);
	push_update_iterators(cont);
	return ;
}

void	do_pb(t_main_cont *cont, t_deque *curr_moves)
{
	push(&cont->stack_a, &cont->stack_b);
	if (curr_moves)
		curr_moves->add_last(curr_moves, PB);
	push_update_iterators(cont);
	return ;
}
