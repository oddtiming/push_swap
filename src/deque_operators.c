/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:03:32 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/05/01 20:33:40 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	new_deque(t_deque **deque)
{
	*deque = ft_xalloc(sizeof(t_deque));
	init_deque(*deque);
}

t_deque	*clone_deque(t_deque *src)
{
	t_deque	*clone;
	int		i;

	if (!src)
		return (NULL);
	new_deque(&clone);
	i = 0;
	while (i < src->size)
	{
		clone->add_last(clone, src->elems[i]);
		i++;
	}
	return (clone);
}

void	copy_deque(t_deque *src, t_deque *dest)
{
	int	i;

	if (!src || !dest)
		return ;
	dest->reinit_list(dest);
	i = 0;
	while (i < src->size)
	{
		dest->add_last(dest, src->elems[i]);
		i++;
	}
	return ;
}

void	cat_deque(t_deque *src, t_deque *dest)
{
	int	i;

	if (!src || !dest)
		return ;
	i = 0;
	while (i < src->size)
	{
		dest->add_last(dest, src->elems[i]);
		i++;
	}
	return ;
}

void	cat_deque_front(t_deque *src, t_deque *dest)
{
	int	i;

	if (!src || !dest)
		return ;
	i = src->size - 1;
	while (i >= 0)
	{
		dest->add_front(dest, src->elems[i]);
		i--;
	}
	return ;
}
