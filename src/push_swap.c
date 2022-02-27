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
		printf("\n----Initial Stacks----\n\n");
		print_stacks(cont);
	}
	normalize_stack_values(&cont->stack_a);
	if (DEBUG)
	{
		printf("\n----After normalization----\n\n");
		print_stacks(cont);
	}

	// do_ra(cont, &cont->moves_list);

	sort(cont);

	print_all_moves(&cont->moves_list);

	cleanup(cont);
	return (EXIT_SUCCESS);
}
