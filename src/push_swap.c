#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_stacks	stacks;

	printf("sizeof(t_stacks) = %zu\n", sizeof(t_stacks));
	ft_bzero(&stacks, sizeof(t_stacks));
	parse(argc, argv, &stacks);
	print_stacks(&stacks);
	rotate(stacks.A, stacks.sizeA, false);
	printf("\n----After rotate----\n\n");
	print_stacks(&stacks);
	rotate(stacks.A, stacks.sizeA, true);
	rotate(stacks.A, stacks.sizeA, true);
	printf("\n----After 2x reverse rotate----\n\n");
	print_stacks(&stacks);
	return (0);
}
