/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 00:51:48 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/21 01:42:56 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	push(t_deque *stack_src, t_deque *stack_dest)
{
	stack_dest->add_front(stack_dest, stack_src->elems[0]);
	stack_src->remove_front(stack_src);
	return ;
}

void	checker_pa(t_checker *checker)
{
	push(&checker->stack_b, &checker->stack_a);
	return ;
}

void	checker_pb(t_checker *checker)
{
	push(&checker->stack_a, &checker->stack_b);
	return ;
}
