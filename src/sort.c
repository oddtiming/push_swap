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
			nb_sorted++;
		if (i == size)
			i = 0;
		else
			i++;
	}
	return (nb_sorted);
}

int	get_biggest_val(int *stack, int size)
{
	int	pos_in_stack;
	int pos_biggest;
	int	biggest_val;

	pos_in_stack = 0;
	pos_biggest = 0;
	biggest_val = 0;
	while (pos_in_stack < size)
	{
		if (stack[pos_in_stack] > biggest_val)
		{
			biggest_val = stack[pos_in_stack];
			pos_biggest = pos_in_stack;
		}
		pos_in_stack++;
	}
	return (biggest_val);
}

int	get_smallest_val(int *stack, int size)
{
	int	pos_in_stack;
	int smallest_pos;
	int	smallest_val;

	pos_in_stack = 0;
	smallest_pos = 0;
	smallest_val = size;
	while (pos_in_stack < size)
	{
		if (stack[pos_in_stack] < smallest_val)
		{
			smallest_val = stack[pos_in_stack];
			smallest_pos = pos_in_stack;
		}
		pos_in_stack++;
	}
	return (smallest_val);
}

int	get_smallest_pos(int *stack, int size)
{
	int	pos_in_stack;
	int smallest_pos;
	int	smallest_val;

	pos_in_stack = 0;
	smallest_pos = 0;
	smallest_val = size;
	while (pos_in_stack < size)
	{
		if (stack[pos_in_stack] < smallest_val)
		{
			smallest_val = stack[pos_in_stack];
			smallest_pos = pos_in_stack;
		}
		pos_in_stack++;
	}
	return (smallest_pos);
}

void	sort_3(t_main_container *cont)
{
	int	smallest_pos;
	int	nb_sorted;

	smallest_pos = get_smallest_pos(cont->A, cont->sizeA);
	nb_sorted = nb_sorted_at_pos(cont->A, cont->sizeA, smallest_pos);
	if (DEBUG)
		printf("in sort_3, smallest_pos = %d\n", smallest_pos);
	if (smallest_pos == 0 && nb_sorted == cont->size)
		return ;
	else if (nb_sorted == cont->size)
	{
		if (smallest_pos == 1)
			make_rab(&cont->A, cont->sizeA, RA);
		else if (smallest_pos == cont->size - 1)
			make_rrab(&cont->A, cont->sizeA, RRA);
		return ;
	}
	make_sab(cont->A, cont->sizeA, SA);
	sort_3(cont);
	return ;
}

void	sort(t_main_container *cont)
{
	if (cont->size <= 3)
		sort_3(cont);

	else if (cont->size <= 5)
		sort_5(cont);
	return ;
}
