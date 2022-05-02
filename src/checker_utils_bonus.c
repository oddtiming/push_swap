/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:04:45 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/30 19:04:45 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	init_bonus(t_checker *checker, char **args)
{
	int	i;

	init_deque(&checker->stack_a);
	init_deque(&checker->stack_b);
	checker->moves_fcts = ft_xalloc(11 * sizeof(void *));
	i = -1;
	while (args[++i] != NULL)
		checker->stack_a.add_last(&checker->stack_a, ft_atoi(args[i]));
	set_moves_pointers(checker->moves_fcts);
	return ;
}

void	bonus_exit_on_err(t_checker *checker, char *curr_line)
{
	free(curr_line);
	close(STDIN_FILENO);
	read_line(STDIN_FILENO);
	free_checker(checker);
	ft_putstr_fd("Error\n", STDERR_FILENO);
	exit (255);
}

void	free_checker(t_checker *checker)
{
	checker->stack_a.free_list(&checker->stack_a);
	checker->stack_b.free_list(&checker->stack_b);
	free(checker->moves_fcts);
	free(checker);
	return ;
}
