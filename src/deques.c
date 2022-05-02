/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deques.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:26:11 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/05/01 20:20:36 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deques.h"

void	init_deque(t_deque *deque)
{
	deque->add_front = &deque_add_front;
	deque->add_last = &deque_add_last;
	deque->free_list = &deque_free_list;
	deque->get_elem_max = &deque_get_elem_max;
	deque->get_elem_min = &deque_get_elem_min;
	deque->reinit_list = &deque_reinit_list;
	deque->remove_front = &deque_remove_front;
	deque->remove_last = &deque_remove_last;
	deque->resize_end = &deque_resize_end;
	deque->resize_front = &deque_resize_front;
	deque->set_elem = &deque_set_elem;
	deque->size = 0;
	deque->min_elem = deque->get_elem_min(deque);
	deque->max_elem = deque->get_elem_max(deque);
	deque->capacity_end = VECTOR_INIT_SIZE;
	deque->capacity_front = VECTOR_INIT_SIZE;
	deque->capacity_total = 2 * VECTOR_INIT_SIZE;
	deque->malloced_space = ft_xalloc(2 * VECTOR_INIT_SIZE * sizeof(int));
	deque->elems = &(deque->malloced_space[VECTOR_INIT_SIZE]);
	return ;
}

void	deque_reinit_list(t_deque *deque)
{
	free(deque->malloced_space);
	deque->size = 0;
	deque->min_elem = INT_MAX - 100;
	deque->max_elem = INT_MIN + 100;
	deque->capacity_end = VECTOR_INIT_SIZE;
	deque->capacity_front = VECTOR_INIT_SIZE;
	deque->capacity_total = 2 * VECTOR_INIT_SIZE;
	deque->malloced_space = ft_xalloc(2 * VECTOR_INIT_SIZE * sizeof(int));
	deque->elems = deque->malloced_space + VECTOR_INIT_SIZE;
	return ;
}
