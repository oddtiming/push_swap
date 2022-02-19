#include "push_swap.h"

int	nb_sorted_at_pos(int *stack, int size, int pos)
{
	int		nb_sorted;
	int		curr_value;
	int		i;

	i = pos + 1;
	nb_sorted = 1;
	while (i != pos && !(pos == 0 && i == size))
	{
		if (i == size)
			curr_value = stack[0];
		else
			curr_value = stack[i];
		if (i == 0)
		{
			i++;
			continue ;
		}
		if (curr_value > stack[i - 1])
		{
			nb_sorted++;
			if (DEBUG)
				printf("\033[0;33mstack[%d] > stack[%d] <===> %d > %d \n\033[0m", (i != size)*i, i-1, curr_value, stack[i - 1]);
		}
		else if (DEBUG)
			printf("\033[0;33mstack[%d] !> stack[%d] <===> %d !> %d \n\033[0m", (i != size)*i, i-1, curr_value, stack[i - 1]);
		if (i == size)
			i = 0;
		else
			i++;
	}
	if (DEBUG)
		printf("nb_sorted at stack[%d] == %d\n", pos, nb_sorted);
	return (nb_sorted);
}

int	nb_sorted_at_smallest(int *stack, int size, int *pos_smallest)
{
	int	pos_in_stack;
	int	value_smallest;

	pos_in_stack = 0;
	value_smallest = size;
	while (pos_in_stack < size)
	{
		if (stack[pos_in_stack] < value_smallest)
		{
			value_smallest = stack[pos_in_stack];
			*pos_smallest = pos_in_stack;
		}
		pos_in_stack++;
	}
	return (nb_sorted_at_pos(stack, size, *pos_smallest));
}

void	sort_3(t_stacks *stacks)
{
	int	pos_smallest;
	int	nb_sorted;

	pos_smallest = 0;
	nb_sorted = nb_sorted_at_smallest(stacks->A, stacks->sizeA, &pos_smallest);
	if (DEBUG)
		printf("in sort_3, pos_smallest = %d\n", pos_smallest);
	if (pos_smallest == 0 && nb_sorted == stacks->size)
		return ;
	else if (nb_sorted == stacks->size)
	{
		if (pos_smallest == 1)
			make_move(stacks, RA);
		else if (pos_smallest == stacks->size - 1)
			make_move(stacks, RRA);
		return ;
	}
	make_move(stacks, SA);
	sort_3(stacks);
	return ;
}

void	sort(t_stacks *stacks)
{
	if (stacks->size <= 3)
		sort_3(stacks);

	return ;
}
