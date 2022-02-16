#include "push_swap.h"

int	nb_sorted_at_pos(int *stack, int size, int pos)
{
	int		nb_sorted;
	int		curr_value;
	int 	i;

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

int	stack_is_sorted_at_pos(int *stack, int size)
{
	int	stack_pos;
	int	nb_sorted;

	stack_pos = 0;
	while (stack[stack_pos] != 0 && stack_pos < size)
		stack_pos++;
	if (stack[stack_pos] != 0)
		exit_on_err("Oops, you forgot the conversion, so there's no zero :(((((\n");
	nb_sorted = nb_sorted_at_pos(stack, size, stack_pos);
	if (nb_sorted == size)
	{
		if (DEBUG)
			printf("in stack_order_at_pos, stack_pos of sorted == %d\n", stack_pos);
		return (stack_pos);
	}
	return (-1);
}

void	sort_3(t_stacks *stacks)
{
	int pos_of_sorted;

	pos_of_sorted = stack_is_sorted_at_pos(stacks->A, stacks->sizeA);
	if (DEBUG)
		printf("in sort_3, pos_of_sorted = %d\n", pos_of_sorted);
	if (pos_of_sorted > -1)
	{
		if (pos_of_sorted == 1)
			make_move(stacks, RA);
		else if (pos_of_sorted == stacks->size - 1)
			make_move(stacks, RRA);
		return ;
	}
	make_move(stacks, SA);
	sort_3(stacks);
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
