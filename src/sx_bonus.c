/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sx_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 01:02:15 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/21 01:41:59 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	swap(t_deque *stack)
{
	int	temp;

	temp = stack->elems[0];
	stack->set_elem(stack, 0, stack->elems[1]);
	stack->set_elem(stack, 1, temp);
	return ;
}

void	checker_sa(t_checker *checker)
{
	swap(&checker->stack_a);
	return ;
}

void	checker_sb(t_checker *checker)
{
	swap(&checker->stack_b);
	return ;
}

void	checker_ss(t_checker *checker)
{
	swap(&checker->stack_a);
	swap(&checker->stack_b);
	return ;
}
