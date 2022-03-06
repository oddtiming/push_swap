#include <stdio.h>
#include <stdbool.h>
#include "../libft/libft.a"

int		*split_args(int *argc, char *argv[]);
void	exit_on_err(char *err_message);

int	divide_stack(int *stack, int size)
{

}

int	main(int argc, char *argv[])
{
	int	*stack;
	int	*stack_divided;
	int	stack_size;

	if (argc == 1)
		exit_on_err("received no argument");
	stack = split_args(argc, argv);
	stack_size = argc - 1;

	stack_divided = divide_stack(stack, stack_size);

	free(stack);
	free(stack_divided);
	return (0);
}

int	*split_args(int *argc, char *argv[])
{
	char	**temp_split;
	int		*stack;
	int		i;

	if (*argc == 2)
	{
		temp_split = ft_split(argv[1], ' ');
		if (!temp_split)
			exit_on_err("malloc oopsie unlucky fucky :((( \n");
		*argc -= 1;
		while (argv[*argc])
			*argc += 1;
		argv = temp_split;
	}
	stack = malloc((*argc) * sizeof(int));
	if (!stack)
		exit_on_err("malloc oopsie unlucky fucky :((( \n");
	i = 0;
	while (++i < *argc)
		stack[i - 1] = ft_atoi(argv[i]);
	stack[i] = NULL;
	return (stack);
}

void	exit_on_err(char *err_message)
{
	write(STDERR_FILENO, err_message, ft_strlen(err_message));
	exit (EXIT_FAILURE);
}
