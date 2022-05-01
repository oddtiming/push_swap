/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:04:42 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/05/01 14:38:22 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

void	set_moves_pointers(void (**array)(t_checker *))
{
	array[SA_INDEX] = checker_sa;
	array[SB_INDEX] = checker_sb;
	array[SS_INDEX] = checker_ss;
	array[RA_INDEX] = checker_ra;
	array[RB_INDEX] = checker_rb;
	array[RR_INDEX] = checker_rr;
	array[RRA_INDEX] = checker_rra;
	array[RRB_INDEX] = checker_rrb;
	array[RRR_INDEX] = checker_rrr;
	array[PA_INDEX] = checker_pa;
	array[PB_INDEX] = checker_pb;
	return ;
}

static bool	is_a_move(char *curr_line)
{
	int	strlen;

	strlen = ft_strlen(curr_line);
	if (strlen < 2)
		return (false);
	if (curr_line[strlen - 1] == '\n')
		strlen--;
	else
		return (false);
	if (!ft_strncmp(curr_line, "rr", strlen)
		|| !ft_strncmp(curr_line, "ra", strlen)
		|| !ft_strncmp(curr_line, "rb", strlen)
		|| !ft_strncmp(curr_line, "rrr", strlen)
		|| !ft_strncmp(curr_line, "rra", strlen)
		|| !ft_strncmp(curr_line, "rrb", strlen)
		|| !ft_strncmp(curr_line, "ss", strlen)
		|| !ft_strncmp(curr_line, "sa", strlen)
		|| !ft_strncmp(curr_line, "sb", strlen)
		|| !ft_strncmp(curr_line, "pa", strlen)
		|| !ft_strncmp(curr_line, "pb", strlen))
		return (true);
	return (false);
}

void	do_moves(t_checker *checker)
{
	char	*curr_line;
	int		move;
	int		i;
	int		line_number;

	curr_line = read_line(STDIN_FILENO);
	line_number = 0;
	while (curr_line)
	{
		line_number++;
		if (!is_a_move(curr_line))
			bonus_exit_on_err(checker, curr_line);
		move = 0;
		i = 0;
		while (curr_line[i] && curr_line[i] != '\n')
			move = (move << 8) | curr_line[i++];
		checker->moves_fcts[convert_move_to_index(move)](checker);
		free(curr_line);
		curr_line = read_line(STDIN_FILENO);
	}
	return ;
}

int	main(int argc, char *argv[])
{
	t_checker	*checker;
	int			i;

	if (argc < 2)
		exit(EXIT_SUCCESS);
	checker = ft_xalloc(sizeof(t_checker));
	parse_bonus(checker, argc, argv);
	do_moves(checker);
	i = 0;
	while (++i < checker->stack_a.size)
	{
		if (checker->stack_a.elems[i] < checker->stack_a.elems[i - 1])
		{
			write(STDOUT_FILENO, "KO\n", 3);
			free_checker(checker);
			return (0);
		}
	}
	write(STDOUT_FILENO, "OK\n", 3);
	free_checker(checker);
	return (0);
}
