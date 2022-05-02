/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:07:25 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 22:07:25 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	cleanup(t_main_cont *cont)
{
	cont->stack_a.free_list(&cont->stack_a);
	cont->stack_b.free_list(&cont->stack_b);
	cont->curr_moves.free_list(&cont->curr_moves);
	cont->best_moves.free_list(&cont->best_moves);
	cont->best_moves.free_list(&cont->initial_stack);
	cont->best_moves.free_list(&cont->staying_vals);
	cont->best_moves.free_list(&cont->leaving_vals);
	free (cont->reverse_fcts);
	free (cont);
	return ;
}
