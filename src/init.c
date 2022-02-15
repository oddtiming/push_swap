#include "push_swap.h"

void	assign_inputs(char **args, t_stacks *stacks)
{
	int	i;

	stacks->A = malloc(stacks->size * sizeof(int));
	stacks->B = malloc(stacks->size * sizeof(int));
	printf("size : %d\n", stacks->size);
	if (!stacks->A || !stacks->B)
		exit_on_err("Malloc error\n");
	i = 0;
	while (args[i])
	{
		stacks->A[i] = ft_atoi(args[i]);
		i++;
	}
	stacks->sizeA = stacks->size;
	return ;
}
