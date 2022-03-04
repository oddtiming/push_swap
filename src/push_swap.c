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

	// insert_b(cont, &cont->final_moves);	

	// do_pb(cont, &cont->curr_moves);
	// do_ra(cont, &cont->curr_moves);
	// do_pb(cont, &cont->curr_moves);
	// try_swap(cont);
	// print_all_moves(&cont->best_moves);


	sort(cont);

	print_all_moves(&cont->final_moves);
	if (DEBUG)
	{
		print_stacks_info(cont);
	}

	cleanup(cont);
	return (EXIT_SUCCESS);
}
