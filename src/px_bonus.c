/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 00:51:48 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/21 01:02:12 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

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
