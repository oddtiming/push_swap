/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:07:44 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 22:07:44 by iyahoui-         ###   ########.fr       */
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
