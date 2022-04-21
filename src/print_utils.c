/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:41:28 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 16:43:21 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_move(int move)
{
	char	c;

	if (move >> 16 & 0xFF)
	{
		c = (char)(move >> 16 & 0xFF);
		write(1, &c, 1);
	}
	c = (char)(move >> 8 & 0xFF);
	write(1, &c, 1);
	c = (char)(move & 0xFF);
	write(1, &c, 1);
	write(1, "\n", 1);
	return ;
}

void	print_all_moves(t_deque *curr_moves)
{
	int	pos_of_the_move_thing_in_the_list_thing;

	pos_of_the_move_thing_in_the_list_thing = 0;
	if (curr_moves->size == INT_MAX)
		return ;
	while (pos_of_the_move_thing_in_the_list_thing < curr_moves->size)
	{
		print_move(curr_moves->elems[pos_of_the_move_thing_in_the_list_thing]);
		pos_of_the_move_thing_in_the_list_thing++;
	}
	return ;
}
