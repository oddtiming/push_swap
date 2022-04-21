/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:31:33 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 21:31:33 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_main_cont	*cont;

	if (argc < 2)
		exit(EXIT_FAILURE);
	cont = ft_safealloc(sizeof(t_main_cont));
	parse(argc, argv, cont);
	sort(cont);
	print_all_moves(&cont->best_moves);
	cleanup(cont);
	return (EXIT_SUCCESS);
}
