<<<<<<< HEAD
#include "../incl/push_swap.h"

void	init(char **args, t_stacks *stacks, int size)
=======
#include "push_swap.h"

void	assign_inputs(char **args, t_stacks *stacks)
>>>>>>> bb035a462ef6f279bbacbc4c237da89c8100a6a2
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
<<<<<<< HEAD
=======
	stacks->sizeA = stacks->size;
>>>>>>> bb035a462ef6f279bbacbc4c237da89c8100a6a2
	return ;
}
