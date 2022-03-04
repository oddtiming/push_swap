#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_main_cont	*cont;

	cont = malloc(sizeof(t_main_cont));
	if (!cont)
		exit_on_err("t_main_cont malloc error");
	ft_bzero(cont, sizeof(t_main_cont));
	parse(argc, argv, cont);
	if (DEBUG)
	{
		printf("size of main struct is %zu, lol\n", sizeof(t_main_cont));
		printf("\n----After normalization----\n\n");
		print_stacks_info(cont);
	}

	// iterator *iter;

	// iter = malloc(sizeof(t_iterator);
	// if (!iter)
	// 	exit_on_err(""main: iter error\n);
	// set_iterator(iter, 0, cont->stack_a.size, 0);
	// while (iterate_n_loops(iter, 1))
	// {
	// 	if ()
	// }

	while (cont->stack_a.size > 3)
	{
		// if (cont->stack_a.elems[0] > cont->stack_a.elems[1])
			do_pb(cont, &cont->final_moves);
		// else
		// 	do_ra(cont, &cont->final_moves);
	}
	if (!is_sorted(&cont->stack_a, cont->head_a.index))
		do_sa(cont, &cont->final_moves);
	insert_b(cont, &cont->final_moves);
	rotate_to_0_in_a(cont, &cont->final_moves, cont->head_a.index);
	// print_stacks(cont);
	print_all_moves(&cont->final_moves);
	// printf(MAGENTA"\t==> FINAL TOTAL: %d \n"RESET_COL, cont->final_moves.size);
	// print_stacks_info(cont);

	// do_ra(cont, &cont->curr_moves);
	// do_pb(cont, &cont->curr_moves);
	// try_swap(cont);
	// print_all_moves(&cont->best_moves);


	// sort(cont);

	// print_all_moves(&cont->final_moves);
	// if (DEBUG)
	// {
	// 	print_stacks_info(cont);
	// }

	cleanup(cont);
	return (EXIT_SUCCESS);
}
