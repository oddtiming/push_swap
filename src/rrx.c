/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:08:09 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/21 00:23:12 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rev_rotate(t_deque *stack)
{
	stack->add_front(stack, stack->elems[stack->size - 1]);
	stack->remove_last(stack);
	return ;
}

static inline void	rev_rotate_update_iterators(t_iterator *iterator)
{
	iterate_once(iterator, false);
	return ;
}

void	do_rra(t_main_cont *cont, t_deque *curr_moves)
{
	rev_rotate(&cont->stack_a);
	if (curr_moves)
		curr_moves->add_last(curr_moves, RRA);
	rev_rotate_update_iterators(&cont->head_a);
	return ;
}

void	do_rrb(t_main_cont *cont, t_deque *curr_moves)
{
	rev_rotate(&cont->stack_b);
	if (curr_moves)
		curr_moves->add_last(curr_moves, RRB);
	rev_rotate_update_iterators(&cont->head_b);
	return ;
}

void	do_rrr(t_main_cont *cont, t_deque *curr_moves)
{
	rev_rotate(&cont->stack_a);
	rev_rotate(&cont->stack_b);
	if (curr_moves)
		curr_moves->add_last(curr_moves, RRR);
	rev_rotate_update_iterators(&cont->head_b);
	rev_rotate_update_iterators(&cont->head_a);
	return ;
}
