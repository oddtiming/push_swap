#include "push_swap.h"

void	assign_inputs(t_main_container *cont, char **args, int size)
{
	int	i;

	cont->size = size;
	if (DEBUG)
	{
		printf("in assign_inputs size = %d\n", size);
		printf("in assign_inputs malloced_size = %d\n", 6 * size);
	}
	cont->malloced_space = malloc(6 * size * sizeof(int));
	if (!cont->malloced_space)
		exit_on_err("Malloc error\n");
	cont->A = &(cont->malloced_space[1 * size]);
	cont->B = &(cont->malloced_space[4 * size]);
	i = 0;
	while (args[i])
	{
		cont->A[i] = ft_atoi(args[i]);
		i++;
	}
	cont->sizeA = cont->size;
	cont->sizeB = 0;
	return ;
}
