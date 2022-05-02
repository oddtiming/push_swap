/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rx.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 15:45:17 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/21 00:23:03 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_deque *stack)
{
	stack->add_last(stack, stack->elems[0]);
	stack->remove_front(stack);
	return ;
}

static inline void	rotate_update_iterators(t_iterator *iterator)
{
	iterate_once(iterator, true);
	return ;
}

void	do_ra(t_main_cont *cont, t_deque *curr_moves)
{
	rotate(&cont->stack_a);
	if (curr_moves)
		curr_moves->add_last(curr_moves, RA);
	rotate_update_iterators(&cont->head_a);
	return ;
}

void	do_rb(t_main_cont *cont, t_deque *curr_moves)
{
	rotate(&cont->stack_b);
	if (curr_moves)
		curr_moves->add_last(curr_moves, RB);
	rotate_update_iterators(&cont->head_b);
	return ;
}

void	do_rr(t_main_cont *cont, t_deque *curr_moves)
{
	rotate(&cont->stack_a);
	rotate(&cont->stack_b);
	if (curr_moves)
		curr_moves->add_last(curr_moves, RR);
	rotate_update_iterators(&cont->head_a);
	rotate_update_iterators(&cont->head_b);
	return ;
}
