/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_modify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:26:19 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/05/01 20:27:42 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deques.h"

void	deque_add_front(t_deque *deque, int new_elem)
{
	if (deque->capacity_front == 0)
		deque_resize_front(deque, deque->capacity_total * 2);
	deque->elems -= 1;
	deque->elems[0] = new_elem;
	deque->size += 1;
	deque->capacity_front -= 1;
	deque->capacity_end += 1;
	if (new_elem > deque->max_elem)
		deque->max_elem = new_elem;
	if (new_elem < deque->min_elem)
		deque->min_elem = new_elem;
	return ;
}

void	deque_add_last(t_deque *deque, int new_elem)
{
	if (deque->size == deque->capacity_end)
		deque_resize_end(deque, deque->capacity_total * 2);
	deque->elems[deque->size] = new_elem;
	deque->size += 1;
	if (new_elem > deque->max_elem)
		deque->max_elem = new_elem;
	if (new_elem < deque->min_elem)
		deque->min_elem = new_elem;
	return ;
}

//Need to add resize smaller when under a certain size
void	deque_remove_front(t_deque *deque)
{
	int	elem_to_be_removed;

	elem_to_be_removed = deque->elems[0];
	deque->elems[0] = 0;
	deque->elems += 1;
	deque->capacity_front += 1;
	deque->capacity_end -= 1;
	deque->size -= 1;
	if (elem_to_be_removed == deque->min_elem)
		deque->min_elem = deque->get_elem_min(deque);
	if (elem_to_be_removed == deque->max_elem)
		deque->max_elem = deque->get_elem_max(deque);
	return ;
}

//Need to add resize smaller when under a certain size
void	deque_remove_last(t_deque *deque)
{
	int	elem_to_be_removed;

	elem_to_be_removed = deque->elems[deque->size - 1];
	deque->elems[deque->size - 1] = 0;
	deque->size -= 1;
	if (elem_to_be_removed == deque->min_elem)
		deque->min_elem = deque->get_elem_min(deque);
	if (elem_to_be_removed == deque->max_elem)
		deque->max_elem = deque->get_elem_max(deque);
	return ;
}

void	deque_set_elem(t_deque *deque, int pos, int new_value)
{
	deque->elems[pos] = new_value;
	return ;
}
