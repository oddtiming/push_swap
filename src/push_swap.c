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
	// cont.a = normalize_stack_values(cont.a, cont.sizeA);
	if (DEBUG)
	{
		printf("\n----After normalization----\n\n");
		print_stacks(&cont);
	}
	print_stacks(&cont);

	int *temp;

	temp = cont.a.get_elems(&cont.a);
	printf(RED"In main, temp[%d] = %d\n"RESET_COL, 0, temp[0]);
	printf(RED"In main, temp[%d] = %d\n"RESET_COL, 1, temp[1]);
	printf(RED"In main, temp[%d] = %d\n"RESET_COL, 2, temp[2]);
	printf(RED"In main, temp[%d] = %d\n"RESET_COL, 3, temp[3]);
	printf(RED"In main, temp[%d] = %d\n"RESET_COL, 4, temp[4]);
	printf(RED"In main, temp[%d] = %d\n"RESET_COL, 5, temp[5]);
	printf(RED"In main, temp[%d] = %d\n"RESET_COL, 6, temp[6]);
	cleanup(&cont);
	exit (EXIT_SUCCESS);
}
