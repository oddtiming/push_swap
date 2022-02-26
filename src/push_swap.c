#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_main_cont	cont;
	
	ft_bzero(&cont, sizeof(t_main_cont));

	parse(argc, argv, &cont);
	if (DEBUG)
	{
		printf("\n----Initial Stacks----\n\n");
		print_stacks(&cont);
	}
	normalize_stack_values(&cont.stack_a);
	if (DEBUG)
	{
		printf("\n----After normalization----\n\n");
		print_stacks(&cont);
	}

	printf(YELLOW"--INITIAL STACK--\n"RESET_COL);
	print_stacks(&cont);

	// cont.stack_a.remove_front(&cont.stack_a);
	// cont.stack_a.remove_front(&cont.stack_a);
	// cont.stack_a.remove_front(&cont.stack_a);

	// printf("after removing dfirst three elements\n");
	// print_stacks(&cont);

	do_push(&cont, &cont.moves_list, PB);
	do_push(&cont, &cont.moves_list, PB);
	do_rotate(&cont, &cont.moves_list, RR);
	do_swap(&cont, &cont.moves_list, SS);
	do_push(&cont, &cont.moves_list, PA);
	do_push(&cont, &cont.moves_list, PA);

	print_all_moves(&cont.moves_list);

	cleanup(&cont);
	return (EXIT_SUCCESS);
}
