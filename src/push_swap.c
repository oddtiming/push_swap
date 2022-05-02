/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2022/04/20 16:40:52 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/20 16:41:02 by iyahoui-         ###   ########.fr       */
=======
/*   Created: 2022/04/20 21:31:33 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/27 23:42:15 by iyahoui-         ###   ########.fr       */
>>>>>>> aae4d5e87735a81400d9797777a9c7de4307c7e5
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_main_cont	*cont;

	if (argc < 2)
<<<<<<< HEAD
		exit(EXIT_FAILURE);
	cont = ft_safealloc(sizeof(t_main_cont));
	parse(argc, argv, cont);
	if (cont->stack_a.size <= 7)
		sort(cont);
	assign_longest_increasing_subsequence(cont);
	run_algorithms(cont);
=======
		exit(EXIT_SUCCESS);
	cont = ft_xalloc(sizeof(t_main_cont));
	parse(cont, argc, argv);
	sort(cont);
>>>>>>> aae4d5e87735a81400d9797777a9c7de4307c7e5
	print_all_moves(&cont->best_moves);
	cleanup(cont);
	return (EXIT_SUCCESS);
}
