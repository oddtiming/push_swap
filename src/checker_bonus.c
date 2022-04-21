/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 01:02:06 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/21 13:00:44 by iyahoui-         ###   ########.fr       */
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
	array[RRA_INDEX] = &checker_rra;
	array[RRB_INDEX] = &checker_rrb;
	array[RRR_INDEX] = &checker_rrr;
	array[PA_INDEX] = checker_pa;
	array[PB_INDEX] = checker_pb;
	return ;
}

void	init_bonus(t_checker *checker, char **args)
{
	int	i;

	init_deque(&checker->stack_a);
	init_deque(&checker->stack_b);
	checker->moves_fcts = ft_safealloc(11 * sizeof(void *));
	i = -1;
	while (args[++i] != NULL)
		checker->stack_a.add_last(&checker->stack_a, ft_atoi(args[i]));
	set_moves_pointers(checker->moves_fcts);
	return ;
}

void	do_moves(t_checker *checker)
{
	int		move;
	int		pos;
	char	c;

	pos = 0;
	move = 0;
	while (read(STDIN_FILENO, &c, 1))
	{
		pos++;
		move = (move << 8) | c;
		if ((pos == 2 && (c == 'a' || c == 'b' || c == 's' || c == 'r'))
			|| (pos == 3 && (c != 'r' || c != 's' || c != 'a' || c != 'b')))
		{
			checker->moves_fcts[convert_move_to_index(move)](checker);
			pos = 0;
			move = 0;
		}
		if ((pos == 1 && (c == 'r' || c == 'p' || c == 's'))
			|| (pos == 2 && (c == 'r'|| c == 'a' || c == 'b'))
			|| (pos == 3 && (c != 'r' || c == 's' || c == 'a' || c == 'b' || c == '\n' || !c)))
			continue;
		else
		{
			free_checker(checker);
			exit_on_err("Error\n");
		}
	}
}

void	free_checker(t_checker *checker)
{
	checker->stack_a.free_list(&checker->stack_a);
	checker->stack_b.free_list(&checker->stack_b);
	free(checker->moves_fcts);
	free(checker);
	return ;
}

int	main(int argc, char *argv[])
{
	t_checker	*checker;
	int			i;

	if (argc < 2)
		exit(EXIT_SUCCESS);
	checker = ft_safealloc(sizeof(t_checker));
	parse_bonus(checker, argc, argv);
	do_moves(checker);
	i = 0;
	while (++i < checker->stack_a.size)
	{
		if (checker->stack_a.elems[i] > checker->stack_a.elems[i] - 1)
		{
			write(STDIN_FILENO, "KO\n", 3);
			free_checker(checker);
			return (1);
		}
	}
	write(STDIN_FILENO, "OK\n", 3);
	free_checker(checker);
	return (0);
}
