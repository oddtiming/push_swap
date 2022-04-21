/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:51:01 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 16:36:35 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	*ft_safealloc(size_t size)
{
	void	*mem_space;

	mem_space = malloc(size);
	if (!mem_space)
	{
		write(STDERR_FILENO, "Malloc Error\n", 13);
		exit (EXIT_FAILURE);
	}
	return (mem_space);
}

//Get the pos in the stack of a given value. If not found (-1) is returned
int	get_pos_of_val(t_deque *stack, int val)
{
	int	pos;

	pos = 0;
	while (pos < stack->size)
	{
		if (stack->elems[pos] == val)
			return (pos);
		pos++;
	}
	return (-1);
}

int	get_pos_smallest_val(t_deque *stack)
{
	int	pos_in_stack;

	pos_in_stack = 0;
	if (stack->size <= 0)
		return (0);
	while (stack->elems[pos_in_stack] != stack->min_elem)
		pos_in_stack++;
	return (pos_in_stack);
}

int	get_pos_biggest_val(t_deque *stack)
{
	int	pos_in_stack;

	pos_in_stack = 0;
	if (stack->size <= 0)
		return (0);
	while (stack->elems[pos_in_stack] != stack->max_elem)
		pos_in_stack++;
	return (pos_in_stack);
}

// Will return the next bigger value in the index, or stack_x.min_elem
int	get_insert_val(t_deque *stack, int curr_val)
{
	int	pos;
	int	next_bigger;

	if (curr_val + 1 > stack->max_elem)
		return (stack->min_elem);
	next_bigger = curr_val + 1;
	pos = 0;
	while (pos < stack->size)
	{
		if (stack->elems[pos] == next_bigger)
			return (next_bigger);
		pos++;
	}
	return (get_insert_val(stack, curr_val + 1));
}
