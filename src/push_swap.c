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
		printf("\n----After normalization----\n\n");
		print_stacks_info(cont);
	}

	

	// do_pb(cont, &cont->temp_moves);
	// do_pb(cont, &cont->temp_moves);
	// do_sa(cont, &cont->temp_moves);
	// insert_elem_b(cont, 2, 1);
	// do_pb(cont, &cont->temp_moves);
	// do_pb(cont, &cont->temp_moves);
	// do_pb(cont, &cont->temp_moves);
	// do_rr(cont, &cont->temp_moves);
	// do_rr(cont, &cont->temp_moves);
	// do_rrr(cont, &cont->temp_moves);
	// do_rrr(cont, &cont->temp_moves);
	// do_ss(cont, &cont->temp_moves);
	// do_pa(cont, &cont->temp_moves);
	// do_pa(cont, &cont->temp_moves);
	// do_pa(cont, &cont->temp_moves);
	// do_pa(cont, &cont->temp_moves);
	// do_pa(cont, &cont->temp_moves);

	
	// if (try_swap(cont))
	// 	printf("try_swap success\n");
	// else
	// 	printf("try_swap failure\n");
	// insert_b(cont);
	// print_stacks_info(cont);
	
	// invert_4(cont);

	// undo_moves(cont, &cont->temp_moves);


	sort(cont);

	print_all_moves(&cont->final_moves);
	if (DEBUG)
	{
		print_stacks_info(cont);
	}

	cleanup(cont);
	return (EXIT_SUCCESS);
}
