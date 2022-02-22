#include "push_swap.h"

void	rotate_to_pos0(t_stacks *cont, int pos)
{
	int *stack;
	int	size;

	stack = cont->A;
	size = cont->sizeA;
	if (pos < size - pos)
		while (pos-- > 0)
			make_move(cont, RA);
	else
		while (pos++ < size)
			make_move(cont, RRA);
	return ;
}


//I think that my issue is simply that I need to check whether they are in order
//before I attempte to swap
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
		pos_smallest = get_pos_smallest(stack, size);
		if (nb_sorted_at_pos(stack, size, pos_smallest) == size)
		{
			ft_swap_ints(&stack[pos], &stack[pos + 1]);
			if (DEBUG)
			{
				printf("board after swap\n");
				print_stacks(cont);
			}
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
	int	insertion_val;

	while (cont->sizeB)
	{
		if (cont->B[0] < cont->size - 1)
			insertion_val = cont->B[0] + 1;
		else
			insertion_val = 0;
		if (DEBUG)
			printf(RED"------>in insert_b, insertion_val of %d = %d\n"RESET_COL, cont->B[0], insertion_val);
		pos_of_b0_in_a = 0;
		while (cont->A[pos_of_b0_in_a] != insertion_val)
		{
			set_next_index(&pos_of_b0_in_a, cont->sizeA);
			if (pos_of_b0_in_a == 0)
				set_next_index(&insertion_val, cont->size);
		}	
		if (DEBUG)
			printf(RED"------>in insert_b, pos_of %d in a = %d\n"RESET_COL, insertion_val, pos_of_b0_in_a);
		rotate_to_pos0(cont, pos_of_b0_in_a);
		make_move(cont, PA);
	}
	return ;
}

bool	is_almost_sorted(t_stacks *cont)
{
	int pos_smallest;

	pos_smallest = get_pos_smallest(cont->A, cont->sizeA);
	if (nb_sorted_at_pos(cont->A, cont->sizeA, pos_smallest) == cont->sizeA)
	{
		if (cont->sizeA != cont->size)
			insert_b(cont);
		pos_smallest = get_pos_smallest(cont->A, cont->sizeA);
		if (DEBUG)
		{
			printf(RED"#############pos_smallest = %d\n"RESET_COL, pos_smallest);
			printf(RED"#############cont->A[pos_smallest] = %d\n"RESET_COL, cont->A[pos_smallest]);
		}
		rotate_to_pos0(cont, pos_smallest);
		return (true);
	}
	else if (try_swap(cont) == true)
	{
		if (cont->sizeA != cont->size)
			insert_b(cont);
		pos_smallest = get_pos_smallest(cont->A, cont->sizeA);
		if (DEBUG)
		{
			printf(RED"#############pos_smallest = %d\n"RESET_COL, pos_smallest);
			printf(RED"#############cont->A[pos_smallest] = %d\n"RESET_COL, cont->A[pos_smallest]);
		}
		rotate_to_pos0(cont, pos_smallest);
		return (true);
	}
	return (false);
}

//Need to code try_pb (which will try ALL positions in stack A to see which
//is closest to pos_0) to try to see if pushing a single value can allow
//try_swap to sort the 4 remaining ones.
//I believe that the only case that would result in more than 7 moves with this
//method is "4 3 2 1 0" (8 moves). The only way I found to make it in less is :
//	-pb; sa-> 2 3 1 0 | 4 -ra x2; sa-> 0 1 2 3 | 4 -pa; ra-> [DONE] (7 moves)

void	sort_5(t_stacks *cont)
{
	if (is_almost_sorted(cont) == true)
		return ;
	else
	{
		// if (try_pb == true)
		// 	return ;
		make_move(cont, PB);
		sort_5(cont);
	}
	return ;
}
