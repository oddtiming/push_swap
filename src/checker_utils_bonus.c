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

void	bonus_exit_on_err(t_checker *checker, char *curr_line, int fd)
{
	free(curr_line);
	curr_line = read_line(fd);
	while (curr_line)
	{
		free(curr_line);
		curr_line = read_line(fd);
	}
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
