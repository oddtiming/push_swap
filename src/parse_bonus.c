/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:04:38 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/30 19:04:55 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap_bonus.h"

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
	return (ft_split(argv[1], ' '));
}

void	parse_bonus(t_checker *checker, int argc, char *argv[])
{
	char	**args_split;
	int		i;

	args_split = split_args(argc, argv);
	i = 0;
	while (args_split[i] && is_an_int(args_split[i]) == true)
		i++;
	if (args_split[i] != NULL)
	{
		free(checker);
		ft_free_split(args_split);
		exit_on_err("Error\n");
	}
	init_bonus(checker, args_split);
	if (has_duplicates(checker->stack_a.elems, checker->stack_a.size))
	{
		free_checker(checker);
		ft_free_split(args_split);
		exit_on_err("Error\n");
	}
	ft_free_split(args_split);
	return ;
}
