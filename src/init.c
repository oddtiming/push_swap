#include "push_swap.h"

void	assign_inputs(char **args, t_main_container *cont, int size)
{
	int	i;

	cont->size = size;
	if (DEBUG)
	{
		printf("size : %d\n", cont->size);
		printf("malloced size = %d\n", 3 * size);
	}
	cont->malloced_space = malloc(6 * size * sizeof(int));
	if (!cont->malloced_space)
		exit_on_err("Malloc error in assign_inputs\n");
	cont->A = cont->malloced_space + (1 * size);
	cont->B = cont->malloced_space + (4 * size);
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
