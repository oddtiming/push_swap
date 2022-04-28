/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:40:00 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/28 00:15:25 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * @param array	the initial int array
 * @param size	nb_params
 */
static bool	has_duplicates(int *array, int size)
{
	long	curr_pos;
	long	compare_pos;

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
	int		sign;

	if (!str || !*str)
		return (false);
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	if (!ft_isdigit(str[i]))
		return (false);
	int_to_long = str[i] - '0';
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		int_to_long = 10 * int_to_long + (str[i] - '0');
		if ((sign > 0 && int_to_long > INT_MAX)
			|| (sign < 0 && int_to_long * sign < INT_MIN))
			return (false);
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
		args_split = ft_xalloc((argc) * sizeof(char *));
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
void	parse(t_main_cont *cont, int argc, char *argv[])
{
	char	**args_split;
	int		i;

	args_split = split_args(argc, argv);
	i = 0;
	while (args_split[i] && is_an_int(args_split[i]) == true)
		i++;
	if (args_split[i] != NULL)
	{
		free(cont);
		ft_free_split(args_split);
		exit_on_err("Error\n");
	}
	init(cont, args_split);
	if (has_duplicates(cont->stack_a.elems, cont->stack_a.size))
	{
		cleanup(cont);
		ft_free_split(args_split);
		exit_on_err("Error\n");
	}
	ft_free_split(args_split);
	return ;
}
