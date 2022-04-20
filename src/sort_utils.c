/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:53:41 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 15:56:33 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//Since the pos_smallest lives outside the deque (that's really dumb btw),
//pos_smallest needs to be passed as a parameter for now. Should change it soon
//	Returns true if sorted 
//	Returns false if not sorted 
bool	is_sorted(t_deque *stack, int pos_smallest)
{
	t_iterator	iter;

	set_iterator(&iter, pos_smallest, stack->size, 0);
	while (iterate_n_loops(&iter, 1))
	{
		if (!(stack->elems[iter.index] > stack->elems[iter.prev_index]) \
			&& iter.index != iter.head)
		{
			return (false);
		}
	}
	return (true);
}

/**
 * will rotate stack_a to pos in as few moves as possible and add the
 * rotations made to curr_moves
 * 
 * @param cont 			main container
 * @param curr_moves 	moves to which rotations will be added
 * @param pos 			pos to be rotated to pos_0
 */
void	rotate_to_0_in_a(t_main_cont *cont, t_deque *curr_moves, int pos)
{
	if (pos < cont->stack_a.size - pos)
		while (pos-- > 0)
			do_ra(cont, curr_moves);
	else
		while (pos++ < cont->stack_a.size)
			do_rra(cont, curr_moves);
	return ;
}



int	max_elem_leaving(t_main_cont *cont, t_deque *leaving_vals)
{
	int	i;
	int	max_elem;

	i = 0;
	max_elem = -1;
	while (i < leaving_vals->size)
	{
		if (leaving_vals->elems[i] > max_elem
			&& !is_in_stack(&cont->stack_b, leaving_vals->elems[i]))
			max_elem = leaving_vals->elems[i];
		i++;
	}
	return (max_elem);
}
