#include "push_swap.h"

void	rotate_to_pos0(int **stack, int size, int pos)
{
	if (pos < size - pos)
		while (pos-- > 0)
			make_rab(stack, size, RA);
	else
		while (pos++ < size)
			make_rrab(stack, size, RRA);
	if (DEBUG)
	{
		printf(YELLOW"--------AFTER rotate_to_pos0--------\n"RESET_COL);
		print_single_stack(*stack, size);
	}
	return ;
}

bool	try_pb(t_main_container *cont)
{
	int	pos_in_stack;
	int	stack_head;

	pos_in_stack = 0;
	while (pos_in_stack < cont->sizeA)
	{
		push(cont->A, cont->B, &cont->sizeA, &cont->sizeB);
		stack_head = get_pos_smallest(cont->A, cont->sizeA);
		if (nb_sorted_at_pos(cont->A, cont->sizeA, stack_head) == cont->sizeA)
		{}


	}
	return (false);
}

bool	try_swap(t_main_container *cont)
{
	int *stack;
	int size;
	int	pos;
	int	stack_head;

	stack = cont->A;
	size = cont->sizeA;
	pos = 0;
	while (pos < size - 1)
	{
		ft_swap_ints(&stack[pos], &stack[pos + 1]);
		stack_head = get_pos_smallest(stack, size);
		if (nb_sorted_at_pos(stack, size, stack_head) == size)
		{
			ft_swap_ints(&stack[pos], &stack[pos + 1]);
			rotate_to_pos0(&cont->A, cont->sizeA, pos);
			make_sab(cont->A, cont->sizeA, SA);
			return (true);
		}
		else
			ft_swap_ints(&stack[pos], &stack[pos + 1]);
		pos++;
	}
	if (DEBUG)
	{
		printf(YELLOW"--------AFTER try_swap--------\n"RESET_COL);
		print_stacks(cont);
	}
	return (false);
}

bool	try_rotate(int *stack, int size)
{
	int	stack_head;

	stack_head = get_pos_smallest(stack, size);
	if (nb_sorted_at_pos(stack, size, stack_head) == size)
	{
		rotate_to_pos0(&stack, size, stack_head);
		return (true);
	}
	return (false);
}

void	insert_b(t_main_container *cont)
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
		rotate_to_pos0(&cont->A, cont->sizeA, pos_of_b0_in_a);
		make_push(cont, PA);
		if (DEBUG)
		{
			printf(YELLOW"--------AFTER pa--------\n"RESET_COL);
			print_stacks(cont);
		}
	}
	return ;
}

bool	try_rotate_and_swap(t_main_container *cont)
{
	int stack_head;

	stack_head = get_pos_smallest(cont->A, cont->sizeA);
	if (nb_sorted_at_pos(cont->A, cont->sizeA, stack_head) == cont->sizeA)
	{
		if (cont->sizeA != cont->size)
			insert_b(cont);
		stack_head = get_pos_smallest(cont->A, cont->sizeA);
		if (DEBUG)
		{
			printf(RED"#############stack_head = %d\n"RESET_COL, stack_head);
			printf(RED"#############cont->A[stack_head] = %d\n"RESET_COL, cont->A[stack_head]);
		}
		rotate_to_pos0(&cont->A, cont->sizeA, stack_head);
		return (true);
	}
	else if (try_swap(cont) == true)
	{
		if (cont->sizeA != cont->size)
			insert_b(cont);
		stack_head = get_pos_smallest(cont->A, cont->sizeA);
		if (DEBUG)
		{
			printf(RED"#############stack_head = %d\n"RESET_COL, stack_head);
			printf(RED"#############cont->A[stack_head] = %d\n"RESET_COL, cont->A[stack_head]);
		}
		rotate_to_pos0(&cont->A, cont->sizeA, stack_head);
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

void	sort_5(t_main_container *cont)
{
	if (try_rotate_and_swap(cont) == true)
	{
		if (DEBUG)
		{
			printf("--------SOLVED BOARD--------");
			print_stacks(cont);
		}
		return ;
	}
	else
	{
		// if (try_pb == true)
		// 	return ;
		make_push(cont, PB);
		if (DEBUG)
		{
			printf(YELLOW"--------AFTER pb--------\n"RESET_COL);
			print_stacks(cont);
		}
		sort_5(cont);
	}
	return ;
}
