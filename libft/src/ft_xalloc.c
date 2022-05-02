/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xalloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:21:27 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/27 23:03:10 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_xalloc(size_t size)
{
	void	*mem_space;

	mem_space = malloc(size);
	ft_bzero(mem_space, size);
	return (mem_space);
}
