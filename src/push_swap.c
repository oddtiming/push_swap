#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_main_cont	*cont;

	cont = malloc(sizeof(t_main_cont));
	if (!cont)
		exit_on_err("t_main_cont malloc error");
	ft_bzero(cont, sizeof(t_main_cont));
	parse(argc, argv, cont);
	normalize_stack_values(&cont->stack_a);
	if (DEBUG)
	{
		printf("\n----After normalization----\n\n");
		print_stacks(cont);
		print_stacks_info(cont);
	}

	do_pb(cont, &cont->moves_list);
	do_pb(cont, &cont->moves_list);
	do_pb(cont, &cont->moves_list);
	do_pb(cont, &cont->moves_list);
	do_pb(cont, &cont->moves_list);
	// do_sa(cont, &cont->moves_list);
	// do_ss(cont, &cont->moves_list);
	// do_ss(cont, &cont->moves_list);
	// do_rr(cont, &cont->moves_list);
	// do_pa(cont, &cont->moves_list);
	// do_pa(cont, &cont->moves_list);
	// print_stacks_info(cont);
	
	insert_b(cont);

	// undo_moves(cont, &cont->moves_list);
	// sort(cont);

	print_all_moves(&cont->moves_list);

	cleanup(cont);
	return (EXIT_SUCCESS);
}
