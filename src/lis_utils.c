/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lis_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:25:23 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/05/01 20:49:08 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	is_in_stack(t_deque *stack, int val)
{
	int	i;

	i = 0;
	while (i < stack->size)
	{
		if (stack->elems[i] == val)
			return (true);
		i++;
	}
	return (false);
}

void	free_deque_list(t_deque **list, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		list[i]->free_list(list[i]);
		free (list[i]);
		i++;
	}
	free (list);
	return ;
}

void	rotate_stack_to_0(t_deque *stack, int pos)
{
	if (pos < stack->size - pos)
	{
		while (pos-- > 0)
		{
			rotate(stack);
		}
	}
	else
	{
		while (pos++ < stack->size)
		{
			rev_rotate(stack);
		}
	}
	return ;
}
