#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_stacks	stacks;
	
	printf("AT ENTRY, DEBUG == %d\n", DEBUG);
	ft_bzero(&stacks, sizeof(t_stacks));

	parse(argc, argv, &stacks);
	if (DEBUG)
	{
		printf("\n----Initial Stacks----\n\n");
		print_stacks(&stacks);
	}
	stacks.A = normalize_stack_values(stacks.A, stacks.size);
	if (DEBUG)
	{
		printf("\n----After normalization----\n\n");
		print_stacks(&stacks);
	}


	sort(&stacks);
	cleanup(&stacks);
	return (0);
}
	// print_stacks(&stacks);

	// make_move(&stacks, PB);
	// make_move(&stacks, PB);
	// make_move(&stacks, PB);
	// make_move(&stacks, PB);
	// print_stacks(&stacks);

	// make_move(&stacks, RRR);
	// print_stacks(&stacks);
	// make_move(&stacks, RR);
	// print_stacks(&stacks);
	// make_move(&stacks, SS);
	// print_stacks(&stacks);
	// make_move(&stacks, PA);
	// make_move(&stacks, PA);
	// make_move(&stacks, PA);
	// make_move(&stacks, PA);
	// print_stacks(&stacks);
	// make_move(&stacks, RR);
	// print_stacks(&stacks);
	// make_move(&stacks, RRR);
	// print_stacks(&stacks);
	// make_move(&stacks, SS);
	// print_stacks(&stacks);


	// rotate(stacks.A, stacks.sizeA, false);
	// printf("\n----After rotate----\n\n");
	// print_stacks(&stacks);

	// rotate(stacks.A, stacks.sizeA, true);
	// rotate(stacks.A, stacks.sizeA, true);
	// printf("\n----After 2x reverse rotate----\n\n");
	// print_stacks(&stacks);
