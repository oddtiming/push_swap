#include "../incl/push_swap.h"

int	main(int argc, char *argv[])
{
	t_stacks	stacks;
	
	printf("sizeof(t_stacks) = %zu\n", sizeof(t_stacks));
	ft_bzero(&stacks, sizeof(t_stacks));
	parse(argc, argv, &stacks);

	
	return (0);
}
