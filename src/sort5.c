#include "push_swap.h"

void	rotate_to_pos0(t_stacks *cont, int pos)
{
	int *stack;
	int	size;

	stack = cont->A;
	size = cont->sizeA;
	if (pos < size - pos)
		while (pos--)
			make_move(cont, RA);
	else
		while (pos++ != size)
			make_move(cont, RRA);
	return ;
}

bool	try_swap(t_stacks *cont)
{
	int *stack;
	int size;
	int	pos;
	int	pos_smallest;

	stack = cont->A;
	size = cont->sizeA;
	pos = 0;
	while (pos < size - 1)
	{
		ft_swap_ints(&stack[pos], &stack[pos + 1]);
		pos_smallest = get_smallest_pos(stack, size);
		if (nb_sorted_at_pos(stack, size, pos_smallest) == size)
		{
			ft_swap_ints(&stack[pos], &stack[pos + 1]);
			rotate_to_pos0(cont, pos);
			make_move(cont, SA);
			return (true);
		}
		else
			ft_swap_ints(&stack[pos], &stack[pos + 1]);
		pos++;
	}
	if (DEBUG)
	{
		printf("---after try_swap-----\n");
		print_stacks(cont);
	}	

	return (false);
}

void	insert_b(t_stacks *cont)
{
	int	pos_of_b0_in_a;
	int	next_index;

	while (cont->sizeB)
	{
		pos_of_b0_in_a = 0;
		next_index = cont->B[0] + 1;
		if (cont->B[0] == cont->size - 1)
			next_index = 0;
		while (cont->A[pos_of_b0_in_a] != next_index)
			pos_of_b0_in_a++;
		rotate_to_pos0(cont, pos_of_b0_in_a);
		make_move(cont, PA);
	}
	return ;
}

void	sort_5(t_stacks *cont)
{
	int pos_smallest;
	int	nb_sorted;

	pos_smallest = get_smallest_pos(cont->A, cont->sizeA);
	if (DEBUG)
		printf("in sort_5, pos_smallest = %d\n", pos_smallest);
	nb_sorted = nb_sorted_at_pos(cont->A, cont->sizeA, pos_smallest);
	if (nb_sorted == cont->sizeA)
	{
		rotate_to_pos0(cont, pos_smallest);
		return ;
	}
	if (try_swap(cont) == true)
	{
		rotate_to_pos0(cont, get_smallest_pos(cont->A, cont->sizeA));
		return ;
	}
	while (cont->sizeA > 3)
	{
		make_move(cont, PB);
		if (try_swap(cont) == true)
		{
			insert_b(cont);
			rotate_to_pos0(cont, get_smallest_pos(cont->A, cont->sizeA));
			return ;
		}
	}
}
