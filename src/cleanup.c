#include "push_swap.h"

void	cleanup(t_stacks *stacks)
{
	free (stacks->A);
	free (stacks->B);
	return ;
}
