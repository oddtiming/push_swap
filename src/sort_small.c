/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_x.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:25:35 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 23:25:55 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	check_if_best_moves(t_main_cont *cont, t_deque *moves_buff)
{
	int	total_nb_moves;

	if (!is_sorted(&cont->stack_a, cont->head_a.index))
	{
		return (false);
	}
	total_nb_moves = cont->curr_moves.size;
	if (moves_buff)
		total_nb_moves += moves_buff->size;
	if (total_nb_moves < cont->min_nb_moves)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
		cat_deque(moves_buff, &cont->best_moves);
		cont->min_nb_moves = cont->best_moves.size;
	}
	return (false);
}

bool	try_solution(t_main_cont *cont, t_deque *moves_buff)
{
	if (is_sorted(&cont->stack_a, cont->head_a.index) && \
		moves_buff->size + cont->curr_moves.size < cont->min_nb_moves)
	{
		insert_b(cont, moves_buff);
		rotate_to_0_in_a(cont, moves_buff, cont->head_a.index);
		if (check_if_best_moves(cont, moves_buff))
		{
			discard_moves(cont, moves_buff);
			return (true);
		}
	}
	return (false);
}

bool	try_swap(t_main_cont *cont)
{
	t_deque	*moves_buff;
	int		curr_pos;

	curr_pos = 0;
	moves_buff = NULL;
	while (curr_pos < cont->stack_a.size)
	{
		new_deque(&moves_buff);
		rotate_to_0_in_a(cont, moves_buff, curr_pos);
		do_sa(cont, moves_buff);
		if (try_solution(cont, moves_buff))
			return (true);
		discard_moves(cont, moves_buff);
		curr_pos++;
	}
	return (false);
}

void	try_sort_small(t_main_cont *cont)
{
	t_deque	*moves_buff;		
	int		curr_pos;

	if (cont->stack_a.size < 3)
		return ;
	moves_buff = NULL;
	curr_pos = 0;
	while (curr_pos < cont->stack_a.size)
	{
		if (cont->stack_a.size == 4)
			try_invert_4(cont);
		new_deque(&moves_buff);
		try_swap(cont);
		try_solution(cont, moves_buff);
		rotate_to_0_in_a(cont, moves_buff, curr_pos);
		do_pb(cont, moves_buff);
		cat_deque(moves_buff, &cont->curr_moves);
		try_sort_small(cont);
		undo_n_moves(cont, &cont->curr_moves, moves_buff->size);
		moves_buff->free_list(moves_buff);
		free(moves_buff);
		moves_buff = NULL;
		curr_pos++;
	}
	return ;
}

bool	try_invert_4(t_main_cont *cont)
{
	t_deque	*moves_buff;

	moves_buff = NULL;
	new_deque(&moves_buff);
	do_sa(cont, moves_buff);
	do_ra(cont, moves_buff);
	do_ra(cont, moves_buff);
	do_sa(cont, moves_buff);
	if (try_solution(cont, moves_buff))
	{
		return (true);
	}
	discard_moves(cont, moves_buff);
	return (false);
}
