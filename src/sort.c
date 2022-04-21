/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:38:42 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 16:38:42 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_small(t_main_cont *cont)
{
	if (cont->stack_a.size == 2 && !is_sorted(&cont->stack_a, 0))
		do_sa(cont, &cont->best_moves);
	else
		try_sort_small(cont);
	return ;
}

void	sort(t_main_cont *cont)
{
	if (cont->stack_a.size <= 7)
		sort_small(cont);
	else
		return ;
	print_all_moves(&cont->best_moves);
	cleanup(cont);
	exit(EXIT_SUCCESS);
	return ;
}
