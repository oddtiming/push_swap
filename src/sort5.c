#include "push_swap.h"

void	rotate_to_0(t_stacks *stacks)
{
	int *stack;
	int	dist_from_origin;
	int	size;

	stack = stacks->A;
	size = stacks->sizeA;
	dist_from_origin = 0;
	while (stack[dist_from_origin] != 0)
		dist_from_origin++;
	if (dist_from_origin < size - dist_from_origin)
		while (dist_from_origin--)
			make_move(stacks, RA);
	else
		while (dist_from_origin++ != size)
			make_move(stacks, RRA);
	return ;
}

void	sort5(t_stacks *stacks)
{
	int	nb_sorted;

	nb_sorted = nb_sorted_at_smallest(stacks->A, stacks->sizeA, get0(stacks->A, stacks->sizeA));
	if (nb_sorted == stacks->size)
		rotate_to_0(stacks->A, stacks->Asize);
}
