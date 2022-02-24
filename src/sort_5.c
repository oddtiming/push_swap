#include "push_swap.h"
#define NOT_SORTED -1

void	rotate_a_to_pos0(t_main_cont *cont,  int pos)
{
	if (pos < cont->sizeA - pos)
		while (pos-- > 0)
			make_rab(&cont->A, cont->sizeA, RA);
	else
		while (pos++ < cont->sizeA)
			make_rrab(&cont->A, cont->size, RRA);
	if (DEBUG)
	{
		printf(YELLOW"--------AFTER rotate_a_to_pos0--------\n"RESET_COL);
		print_single_stack(cont->A, cont->sizeA);
	}
	return ;
}

void	rotate_a_to_pos0_dry_run(t_main_cont *cont,  int pos)
{
	if (pos < cont->sizeA - pos)
		while (pos-- > 0)
			rotate(&cont->A, cont->sizeA);
	else
		while (pos++ < cont->sizeA)
			rev_rotate(&cont->A, cont->size);
	return ;
}

bool	try_pb(t_main_cont *cont)
{
	int	pos_in_stack;
	int	stack_head_value;
	int	smallest_val;

	if (DEBUG)
		printf(RED"-----ENTERED try_pb!!!-----\n"RESET_COL);
	smallest_val = get_smallest_val(cont->A, cont->sizeA);
	if (smallest_val > NOT_SORTED)
	{
		rotate_a_to_pos0(cont, smallest_val);
		return (true);
	}
	pos_in_stack = 0;
	stack_head_value = cont->A[0];
	while (pos_in_stack < cont->sizeA)
	{
		rotate_a_to_pos0_dry_run(cont, pos_in_stack);
		push(cont, PB);
		if (DEBUG)
		{
			printf(RED"------after pushing stackA[%d]------\n"RESET_COL, pos_in_stack);
			print_stacks(cont);
			
		}
		if (try_sa_dry_run(cont))
		{
			push(cont, PA);
			rotate_a_to_pos0_dry_run(cont, get_pos_in_stack(cont->A, cont->sizeA, stack_head_value));
			rotate_a_to_pos0(cont, pos_in_stack);
			make_push(cont, PB);
			try_sa(cont);
			insert_b(cont);
			if (DEBUG)
			{
				printf(GREEN"--------try_pb succeeded--------\n"RESET_COL);
				print_stacks(cont);				
			}
			return (true);
		}
		else
		{
			push(cont, PA);
			rotate_a_to_pos0_dry_run(cont, get_pos_in_stack(cont->A, cont->sizeA, stack_head_value));
		}
		pos_in_stack++;
	}
	return (false);
}

bool	try_sa_dry_run(t_main_cont *cont)
{
	int *stack;
	int size;
	int	pos;
	int	stack_head;
	int	next_pos;

	stack = cont->A;
	size = cont->sizeA;
	pos = 0;
	while (pos < size)
	{
		next_pos = get_next_pos(pos, size);
		ft_swap_ints(&stack[pos], &stack[next_pos]);
		stack_head = get_smallest_pos(stack, size);
		if (nb_sorted_at_pos(stack, size, stack_head) == size)
		{
			ft_swap_ints(&stack[pos], &stack[next_pos]);
			return (true);
		}
		else
			ft_swap_ints(&stack[pos], &stack[next_pos]);
		pos++;
	}
	return (false);
}

bool	try_sa(t_main_cont *cont)
{
	int *stack;
	int size;
	int	pos;
	int	stack_head;
	int	next_pos;

	stack = cont->A;
	size = cont->sizeA;
	pos = 0;
	while (pos < size)
	{
		next_pos = get_next_pos(pos, size);
		ft_swap_ints(&stack[pos], &stack[next_pos]);
		stack_head = get_smallest_pos(stack, size);
		if (nb_sorted_at_pos(stack, size, stack_head) == size)
		{
			ft_swap_ints(&stack[pos], &stack[next_pos]);
			rotate_a_to_pos0(cont, pos);
			make_sab(cont->A, cont->sizeA, SA);
			if (DEBUG)
			{
				printf(YELLOW"--------AFTER try_sa--------\n"RESET_COL);
				print_stacks(cont);
			}
			return (true);
		}
		else
			ft_swap_ints(&stack[pos], &stack[next_pos]);
		pos++;
	}
	return (false);
}

int	try_ra_dry_run(t_main_cont *cont)
{
	int	smallest_val;

	smallest_val = get_smallest_pos(cont->A, cont->size);
	if (nb_sorted_at_pos(cont->A, cont->size, smallest_val) == cont->sizeA)
	{
		return (smallest_val);
	}
	return (NOT_SORTED);
}

bool	try_ra(t_main_cont *cont)
{
	int	smallest_val;

	smallest_val = get_smallest_pos(cont->A, cont->size);
	if (nb_sorted_at_pos(cont->A, cont->size, smallest_val) == cont->sizeA)
	{
		rotate_a_to_pos0(cont, smallest_val);
		return (true);
	}
	return (false);
}

void	insert_b(t_main_cont *cont)
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
			set_next_pos(&pos_of_b0_in_a, cont->sizeA);
			if (pos_of_b0_in_a == 0)
				set_next_pos(&insertion_val, cont->size);
		}	
		if (DEBUG)
			printf(RED"------>in insert_b, pos_of %d in a = %d\n"RESET_COL, insertion_val, pos_of_b0_in_a);
		rotate_a_to_pos0(cont, pos_of_b0_in_a);
		make_push(cont, PA);
		if (DEBUG)
		{
			printf(YELLOW"--------AFTER pa--------\n"RESET_COL);
			print_stacks(cont);
		}
	}
	insertion_val = get_smallest_pos(cont->A, cont->sizeA);
	rotate_a_to_pos0(cont, insertion_val);
	return ;
}

bool	try_rotate_and_swap(t_main_cont *cont)
{
	int stack_head;

	stack_head = get_smallest_pos(cont->A, cont->sizeA);
	if (nb_sorted_at_pos(cont->A, cont->sizeA, stack_head) == cont->sizeA)
	{
		insert_b(cont);
		if (DEBUG)
		{
			printf(RED"#############stack_head = %d\n"RESET_COL, stack_head);
			printf(RED"#############cont->A[stack_head] = %d\n"RESET_COL, cont->A[stack_head]);
		}
		return (true);
	}
	else if (try_sa(cont) == true)
	{
		insert_b(cont);
		if (DEBUG)
		{
			printf(RED"#############stack_head = %d\n"RESET_COL, stack_head);
			printf(RED"#############cont->A[stack_head] = %d\n"RESET_COL, cont->A[stack_head]);
		}
		return (true);
	}
	return (false);
}

//Need to code try_pb (which will try ALL positions in stack A to see which
//is closest to pos_0) to try to see if pushing a single value can allow
//try_sa to sort the 4 remaining ones.
//I believe that the only case that would result in more than 7 moves with this
//method is "4 3 2 1 0" (8 moves). The only way I found to make it in less is :
//	-pb; sa-> 2 3 1 0 | 4 -ra x2; sa-> 0 1 2 3 | 4 -pa; ra-> [DONE] (7 moves)
//-------------------------
//Nope, there's plenty worse, notably "2 1 0 3 4" and "3 4 0 1 2"
//Theoretical minimum stays 8 moves with implementation of 
// invert_4() == sa; ra x2; sa;

void	sort_5(t_main_cont *cont)
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
		if (try_pb(cont) == true)
			return ;
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
