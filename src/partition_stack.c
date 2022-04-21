/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition_stack.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:32:19 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 22:32:19 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	partition_stack_cutoff(t_deque *stack, t_deque *block_ids, int cutoff)
{
	int		i;

	deque_reinit_list(block_ids);
	i = 0;
	while (i < stack->size)
	{
		if (stack->elems[i] > cutoff)
			block_ids->add_last(block_ids, 1);
		else
			block_ids->add_last(block_ids, 0);
		i++;
	}
	return ;
}

void	partition_stack_in_two(t_deque *stack, t_deque *block_ids)
{
	int		i;

	deque_reinit_list(block_ids);
	i = 0;
	while (i < stack->size)
	{
		if (stack->elems[i] > stack->max_elem / 2)
			block_ids->add_last(block_ids, 1);
		else
			block_ids->add_last(block_ids, 0);
		i++;
	}
	return ;
}
