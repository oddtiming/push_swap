#include "push_swap.h"

int	stack_is_in_order_at_pos(int *stack, int size)
{
	int	i;
	int	stack_pos;
	int	nb_sorted;

	stack_pos = 0;
	while (stack_pos < size)
	{
		i = stack_pos + 1;
		nb_sorted = 1;
		while (i != stack_pos)
		{
			if (i == size - 1)
			{
				if (stack[0] > stack[i])
					nb_sorted++;
				i = 0;
				continue;
			}
			if (stack[i] > stack[i - 1])
				nb_sorted++;
			i++;
		}
		if (nb_sorted == size)
		{
			printf("in stack_order_at_pos, stack_pos of sorted == %d\n", stack_pos);
			return (stack_pos);
		}
		stack_pos++;
	}
	return (-1);
}

void	sort_3(t_stacks *stacks)
{
	// int pos_of_order;

	// pos_of_order = stack_is_in_order_at_pos(stacks->A, stacks->sizeA);
	// printf("in sort_3, pos_of_order = %d\n", pos_of_order);

	if (stack_is_in_order_at_pos(stacks->A, stacks->sizeA) == -1)
		make_move(stacks, SA);
	// printf("after SA, pos_of_order = %d\n", pos_of_order);
	if (stack_is_in_order_at_pos(stacks->A, stacks->sizeA) == 1)
		make_move(stacks, RA);
	else
		make_move(stacks, RRA);
	return ;
}

void	sort(t_stacks *stacks)
{
	if (nb_sorted(stacks->A, stacks->sizeA) == stacks->sizeA)
		return ;

	if (stacks->size <= 3)
		sort_3(stacks);

	return ;
}
