/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2022/04/20 16:38:42 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 16:38:42 by iyahoui-         ###   ########.fr       */
=======
/*   Created: 2022/04/20 22:57:48 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/21 00:21:44 by iyahoui-         ###   ########.fr       */
>>>>>>> aae4d5e87735a81400d9797777a9c7de4307c7e5
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_big(t_main_cont *cont)
{
	assign_longest_increasing_subsequence(cont);
	split_in_blocks(cont);
	split_in_two(cont);
	ignore_lis(cont);
	return ;
}

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
<<<<<<< HEAD
		return ;
	print_all_moves(&cont->best_moves);
	cleanup(cont);
	exit(EXIT_SUCCESS);
=======
		sort_big(cont);
>>>>>>> aae4d5e87735a81400d9797777a9c7de4307c7e5
	return ;
}
