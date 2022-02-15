#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_stacks	stacks;
	printf("sizeof(t_stacks) = %zu\n", sizeof(t_stacks));
	ft_bzero(&stacks, sizeof(t_stacks));
	parse(argc, argv, &stacks);
	printf("\n----Initial Stacks----\n\n");
	print_stacks(&stacks);


	make_move(&stacks, PB);
	make_move(&stacks, PB);
	make_move(&stacks, PB);
	make_move(&stacks, PB);
	print_stacks(&stacks);

	make_move(&stacks, RRR);
	print_stacks(&stacks);
	make_move(&stacks, RR);
	print_stacks(&stacks);
	make_move(&stacks, SS);
	print_stacks(&stacks);
	make_move(&stacks, PA);
	make_move(&stacks, PA);
	make_move(&stacks, PA);
	make_move(&stacks, PA);
	print_stacks(&stacks);
	make_move(&stacks, RR);
	print_stacks(&stacks);
	make_move(&stacks, RRR);
	print_stacks(&stacks);
	make_move(&stacks, SS);
	print_stacks(&stacks);


	// rotate(stacks.A, stacks.sizeA, false);
	// printf("\n----After rotate----\n\n");
	// print_stacks(&stacks);

	// rotate(stacks.A, stacks.sizeA, true);
	// rotate(stacks.A, stacks.sizeA, true);
	// printf("\n----After 2x reverse rotate----\n\n");
	// print_stacks(&stacks);

	return (0);
}
