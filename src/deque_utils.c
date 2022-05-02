/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:32:07 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/05/01 20:22:51 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deques.h"

void	deque_free_list(t_deque *deque)
{
	free (deque->malloced_space);
	deque->malloced_space = NULL;
	return ;
}

void	deque_resize_front(t_deque *deque, int new_size)
{
	int		*temp;
	int		total_new_size;
	int		pos_in_deque;

	total_new_size = new_size + deque->capacity_end;
	temp = ft_xalloc(total_new_size * sizeof(int));
	temp += new_size;
	pos_in_deque = 0;
	while (pos_in_deque < deque->size)
	{
		temp[pos_in_deque] = deque->elems[pos_in_deque];
		pos_in_deque++;
	}
	free(deque->malloced_space);
	deque->malloced_space = temp - new_size;
	deque->elems = temp;
	deque->capacity_front = new_size;
	deque->capacity_total = total_new_size;
	return ;
}

void	deque_resize_end(t_deque *deque, int new_size)
{
	int		*temp;
	int		total_new_size;
	int		pos_in_deque;

	total_new_size = new_size + deque->capacity_front;
	temp = ft_xalloc(total_new_size * sizeof(int));
	temp += deque->capacity_front;
	pos_in_deque = 0;
	while (pos_in_deque < deque->size)
	{
		temp[pos_in_deque] = deque->elems[pos_in_deque];
		pos_in_deque++;
	}
	free(deque->malloced_space);
	deque->malloced_space = temp - deque->capacity_front;
	deque->elems = temp;
	deque->capacity_end = new_size;
	deque->capacity_total = total_new_size;
	return ;
}

int	deque_get_elem_max(t_deque *deque)
{
	int			pos_in_stack;
	int			biggest_value;

	biggest_value = INT_MIN;
	pos_in_stack = 0;
	while (pos_in_stack < deque->size)
	{
		if (deque->elems[pos_in_stack] > biggest_value)
			biggest_value = deque->elems[pos_in_stack];
		pos_in_stack++;
	}
	return (biggest_value);
}

int	deque_get_elem_min(t_deque *deque)
{
	int			pos_in_stack;
	int			smallest_value;

	smallest_value = INT_MAX;
	pos_in_stack = 0;
	while (pos_in_stack < deque->size)
	{
		if (deque->elems[pos_in_stack] < smallest_value)
			smallest_value = deque->elems[pos_in_stack];
		pos_in_stack++;
	}
	return (smallest_value);
}
