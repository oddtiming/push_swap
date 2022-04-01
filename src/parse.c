#include "push_swap.h"

/**
 * @param array	the initial int array
 * @param size	nb_params
 */
static bool	has_duplicates(int *array, int size)
{
	int	curr_pos;
	int	compare_pos;

	if (!array || size <= 0)
		return (false);
	curr_pos = 0;
	while (curr_pos < size - 1)
	{
		compare_pos = curr_pos + 1;
		while (compare_pos < size)
		{
			if (array[curr_pos] == array[compare_pos])
				return (true);
			compare_pos++;
		}
		curr_pos++;
	}
	return (false);
}

/**
 * @brief	will check whether all inputs consist of a decimal integer preceded
 *			by `-`, `+`, or nothing
 * @param	str 
 * @return	true: INT_MIN <= input <= INT_MAX
 */
static bool	is_an_int(char *str)
{
	long	int_to_long;
	int		i;

	if (!str || !*str)
		return (false);
	int_to_long = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			int_to_long *= -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		int_to_long = 10 * int_to_long + (str[i] - '0');
		if (int_to_long > INT_MAX || int_to_long < INT_MIN)
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief	will always transform the inputs into a string literals array
 * @return	char** split_args
 */
static char	**split_args(int argc, char *argv[])
{
	int		i;
	char	**args_split;

	if (argc == 2)
		return (ft_split(argv[1], ' '));
	else
		args_split = malloc((argc) * sizeof(char *));
	if (!args_split)
		exit_on_err("Error\n");
	i = 0;
	while (i < argc - 1)
	{
		args_split[i] = ft_strdup(argv[i + 1]);
		if (!args_split[i])
			exit_on_err("Error\n");
		i++;
	}
	args_split[i] = NULL;
	return (args_split);
}

/**
 * @brief accepts a list of ints without duplicates
 */
void	parse(int argc, char *argv[], t_main_cont *cont)
{
	char	**args_split;
	int		i;

	if (argc < 2)
		exit(EXIT_FAILURE);
	args_split = split_args(argc, argv);
	if (!args_split || !args_split[0])
		exit_on_err("Error\n");
	i = 0;
	while (is_an_int(args_split[i]) == true && args_split[i])
		i++;
	if (args_split[i] != NULL)
		exit_on_err("Error\n");
	init(cont, args_split);
	if (has_duplicates(cont->stack_a.elems, cont->stack_a.size))
		exit_on_err("Error\n");
	// ft_print_split(args_split, "argv");
	ft_free_split(args_split);
	return ;
}
