/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rx_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 00:48:28 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/21 01:42:12 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	rotate(t_deque *stack)
{
	stack->add_last(stack, stack->elems[0]);
	stack->remove_front(stack);
	return ;
}

void	checker_ra(t_checker *checker)
{
	rotate(&checker->stack_a);
	return ;
}

void	checker_rb(t_checker *checker)
{
	rotate(&checker->stack_b);
	return ;
}

void	checker_rr(t_checker *checker)
{
	rotate(&checker->stack_a);
	rotate(&checker->stack_b);
	return ;
}
