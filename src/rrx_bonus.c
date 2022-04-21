/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rrx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 01:02:09 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/21 01:02:09 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	checker_rra(t_checker *checker)
{
	rev_rotate(&checker->stack_a);
	return ;
}

void	checker_rrb(t_checker *checker)
{
	rev_rotate(&checker->stack_b);
	return ;
}

void	checker_rrr(t_checker *checker)
{
	rev_rotate(&checker->stack_a);
	rev_rotate(&checker->stack_b);
	return ;
}
