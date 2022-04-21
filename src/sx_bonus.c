/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sx_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 01:02:15 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/21 01:26:37 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

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
