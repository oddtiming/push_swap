#include "../incl/push_swap.h"

static bool	has_duplicates(int *array, int size)
{
	int	i;
	int	j;

	i = 0;
	if (!array || size < 0)
		return (false);
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (array[j] == array[i])
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

//check_inputs will check whether all inputs consist of an integer preceded
//by `-`, `+`, or nothing else, and followed by nothing else after.
//Will return true if all inputs are, false if there is an error or a duplicate
static bool	is_an_int(char *str)
{
	long	to_long;
	int		i;

	if (!str || !*str)
		return (false);
	to_long = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			to_long *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		to_long = 10 * to_long + (str[i] - '0');
		if (to_long > INT_MAX || to_long < INT_MIN)
			return (false);
		i++;
	}
	if (str[i] != '\0')
			return (false);
	return (true);
}

static char	**split_args(int argc, char *argv[])
{
	int		i;
	char	**args_split;

	if (argc == _ARGC_MIN)
		args_split = ft_split(argv[1], ' ');
	else
	{
		args_split = malloc((argc) * sizeof(char *));
		if (!args_split)
			exit_on_err("Malloc Error\n");
		i = 0;
		while (i < argc - 1)
		{
			args_split[i] = ft_strdup(argv[i + 1]);
			if (!args_split[i])
				exit_on_err("Malloc Error\n");
			i++;
		}
		args_split[i] = NULL;
	}
	if (!args_split)
		exit_on_err("Split Error\n");
	return (args_split);	
}

void	parse(int argc, char *argv[], t_stacks *stacks)
{
	char	**args_split;
	int		i;

	if (argc < _ARGC_MIN)
		exit_on_err("Wrong number of inputs\n");
	args_split = split_args(argc, argv);
	if (!args_split || !args_split[0])
		exit_on_err("args_split is somehow NULL?\n");
	i = 0;
	while (is_an_int(args_split[i]) == true && args_split[i])
		i++;
	if (args_split[i] != NULL)
		exit_on_err("one of the inputs is not an int\n");
	stacks->size = i;
	init(args_split, stacks, i);
	if (has_duplicates(stacks->A, stacks->size) == true)
		exit_on_err("Duplicate inputs\n");
	ft_print_split(args_split, "argv");
	ft_free_split(args_split);
	return ;
}
