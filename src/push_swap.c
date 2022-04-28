/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:31:33 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/27 23:42:15 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_main_cont	*cont;

	if (argc < 2)
		exit(EXIT_SUCCESS);
	cont = ft_xalloc(sizeof(t_main_cont));
	parse(cont, argc, argv);
	sort(cont);
	print_all_moves(&cont->best_moves);
	cleanup(cont);
	return (EXIT_SUCCESS);
}
