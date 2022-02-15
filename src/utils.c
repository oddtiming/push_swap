#include "push_swap.h"

void	print_stacks(t_stacks *stacks)
{
	int	i;

	printf("\t\033[38;5;5m[A]\t\033[38;5;6m[B]\n\033[0m");
	printf("------------------------\n");
	i = 0;
	while (i < stacks->size)
	{
		if (!stacks->A[i] && !stacks->B[i])
			return ;
		printf("%d\t", i);
		if (stacks->A[i])
			printf("\033[38;5;5m[%d]\t\033[0m", stacks->A[i]);
		else
			printf("\t\033[0m");
		if (stacks->B[i])
			printf("\033[38;5;6m[%d]\n\033[0m", stacks->B[i]);
		else
			printf("\n\033[0m");
		i++;
	}

}
