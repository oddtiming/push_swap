#include "push_swap.h"

# define YELLOW "\033[0;33m"
# define MAGENTA "\033[0;35m"
# define RED "\033[0;31m"
# define RESET_COL "\033[0m"

int	nb_sorted_at_pos(int *stack, int size, int pos)
{
	int		nb_sorted;
	int		curr_value;
	int		i;
	int		temp;

	i = pos + 1;
	nb_sorted = 1;
	if (DEBUG)
	{
		printf(MAGENTA"in nb_sorted_at_pos, size = %d\n"RESET_COL, size);
		printf(MAGENTA"in nb_sorted_at_pos, pos = %d\n"RESET_COL, pos);
		temp = size;
		while (--temp >= 0)
			printf(MAGENTA"------------------------->in nb_sorted_at_pos, stack[%d] = %d\n"RESET_COL, temp, stack[temp]);
	}	
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
				printf(YELLOW"stack[%d] > stack[%d] <===> %d > %d \n"RESET_COL, (i != size)*i, i-1, curr_value, stack[i - 1]);
		}
		else if (DEBUG)
			printf(YELLOW"stack[%d] !> stack[%d] <===> %d !> %d \n"RESET_COL, (i != size)*i, i-1, curr_value, stack[i - 1]);
		if (i == size)
			i = 0;
		else
			i++;
	}
	if (DEBUG)
		printf("nb_sorted at stack[%d] == %d\n", pos, nb_sorted);
	return (nb_sorted);
}

int	get_smallest_pos(int *stack, int size)
{
	int	pos_in_stack;
	int pos_smallest;
	int	val_smallest;

	pos_in_stack = 0;
	pos_smallest = 0;
	val_smallest = size;
	while (pos_in_stack < size)
	{
		if (stack[pos_in_stack] < val_smallest)
		{
			val_smallest = stack[pos_in_stack];
			pos_smallest = pos_in_stack;
		}
		pos_in_stack++;
	}
	return (pos_smallest);
}

void	sort_3(t_stacks *cont)
{
	int	pos_smallest;
	int	nb_sorted;

	pos_smallest = get_smallest_pos(cont->A, cont->sizeA);
	nb_sorted = nb_sorted_at_pos(cont->A, cont->sizeA, pos_smallest);
	if (DEBUG)
		printf("in sort_3, pos_smallest = %d\n", pos_smallest);
	if (pos_smallest == 0 && nb_sorted == cont->size)
		return ;
	else if (nb_sorted == cont->size)
	{
		if (pos_smallest == 1)
			make_move(cont, RA);
		else if (pos_smallest == cont->size - 1)
			make_move(cont, RRA);
		return ;
	}
	make_move(cont, SA);
	sort_3(cont);
	return ;
}

void	sort(t_stacks *cont)
{
	if (cont->size <= 3)
		sort_3(cont);

	else if (cont->size <= 5)
		sort_5(cont);
	return ;
}
