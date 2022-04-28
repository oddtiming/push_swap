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

bool	is_a_move(char *curr_line)
{
	int	strlen;

	strlen = ft_strlen(curr_line);
	if (strlen < 2)
		return (false);
	if (curr_line[strlen - 1] == '\n')
		strlen--;
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

void	do_moves(t_checker *checker, char *file)
{
	char	*curr_line;
	int		move;
	int		i;
	int		line_number;
	int		fd;

	fd = open(file, O_RDONLY);
	
	curr_line = get_next_line(fd);
	write(1, "entered do_moves\n", 17);
	printf("entered do_moves (printf)\n");
	line_number = 0;
	while (curr_line)
	{
		line_number++;
		printf("Reached line #%d\n", line_number);
		printf("line: \"%s\"\n", curr_line);
		if (!is_a_move(curr_line))
		{
			free(curr_line);
			return ;
		}
		else
		{
			move = 0;
			i = 0;
			while (curr_line[i] && curr_line[i] != '\n')
			{
				move = (move << 8) | curr_line[i];
				i++;
			}
			printf("move_to_index = %d\n", convert_move_to_index(move));
			checker->moves_fcts[convert_move_to_index(move)](checker);
		}
		free(curr_line);
		curr_line = get_next_line(fd);
	}
	char c;
	if (read(fd, &c, 1))
	{
		printf("Error, char = %c\n", c);
	}
	close(fd);
	return ;
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

	if (argc < 3)
		exit(EXIT_SUCCESS);
	checker = ft_xalloc(sizeof(t_checker));
	parse_bonus(checker, argc, argv);
	do_moves(checker, argv[2]);
	i = 0;
	printf("back in main\n");
	while (++i < checker->stack_a.size)
	{
		if (checker->stack_a.elems[i] < checker->stack_a.elems[i - 1])
		{
			printf("checker found to not be sorted\n");
			printf("\n");
			write(STDOUT_FILENO, "KO\n", 3);
			break ;
		}
	}
	if (i == checker->stack_a.size)
	{
		printf("checker found to be sorted");
		write(STDOUT_FILENO, "OK\n", 3);
	}
	free_checker(checker);
	return (0);
}
