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
	normalize_stack_values(&cont.a);
	if (DEBUG)
	{
		printf("\n----After normalization----\n\n");
		print_stacks(&cont);
	}

	printf(YELLOW"--INITIAL STACK--"RESET_COL);
	print_stacks(&cont);


	cleanup(&cont);
	return (0);
}
