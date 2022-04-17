#include "push_swap.h"

//Get the pos in the stack of a given value. If not found (-1) is returned
int	get_pos_of_val(t_deque *stack, int val)
{
	int	pos;

	pos = 0;
	while (pos < stack->size)
	{
		if (stack->elems[pos] == val)
			return (pos);
		pos++;
	}
	return (-1);
}

int	get_pos_smallest_val(t_deque *stack)
{
	int	pos_in_stack;

	pos_in_stack = 0;
	if (stack->size <= 0)
		return (0);
	while (stack->elems[pos_in_stack] != stack->min_elem)
		pos_in_stack++;
	return (pos_in_stack);
}

int	get_pos_biggest_val(t_deque *stack)
{
	int	pos_in_stack;

	pos_in_stack = 0;
	if (stack->size <= 0)
		return (0);
	while (stack->elems[pos_in_stack] != stack->max_elem)
		pos_in_stack++;
	return (pos_in_stack);
}

// Will return the next bigger value in the index, or stack_x.min_elem
int		get_insert_val(t_deque *stack, int curr_val)
{
	int	pos;
	int	next_bigger;

	if (curr_val + 1 > stack->max_elem)
		return (stack->min_elem);
	next_bigger = curr_val + 1;
	pos = 0;
	while (pos < stack->size)
	{
		if (stack->elems[pos] == next_bigger)
			return (next_bigger);
		pos++;
	}
	return (get_insert_val(stack, curr_val + 1));
}



//Since the pos_smallest lives outside the deque (that's really dumb btw),
//pos_smallest needs to be passed as a parameter for now. Should change it soon
//	Returns true if sorted 
//	Returns false if not sorted 
bool	is_sorted(t_deque *stack, int pos_smallest)
{
	t_iterator	iter;

	set_iterator(&iter, pos_smallest, stack->size, 0);
	while (iterate_n_loops(&iter, 1))
	{
		if (!(stack->elems[iter.index] > stack->elems[iter.prev_index]) \
			&& iter.index != iter.head)
		{
			return (false);
		}
	}

	return (true);
}

/**
 * will rotate stack_a to pos in as few moves as possible and add the
 * rotations made to curr_moves
 * 
 * @param cont 			main container
 * @param curr_moves 	moves to which rotations will be added
 * @param pos 			pos to be rotated to pos_0
 */
void	rotate_to_0_in_a(t_main_cont *cont, t_deque *curr_moves, int pos)
{
	if (DEBUG)
	{
		int revpos = pos - cont->stack_a.size;
		printf(YELLOW"rotate_to_pos0=======> pos = %d, revpos = %d\n", pos, revpos);
		if (pos < cont->stack_a.size - pos)
			printf("Choosing ra; %d < %d\n"RESET_COL, pos, -revpos);
		else
			printf("Choosing rra; %d >= %d\n"RESET_COL, pos, -revpos);
	}
	if (pos < cont->stack_a.size - pos)
		while (pos-- > 0)
			do_ra(cont, curr_moves);
	else
		while (pos++ < cont->stack_a.size)
			do_rra(cont, curr_moves);
	return ;
}

void	rotate_stack_to_0(t_deque *stack, int pos)
{
	if (pos < stack->size - pos)
	{
		while (pos-- > 0)
		{
			rotate(stack);
		}
	}
	else
	{
		while (pos++ < stack->size)
		{
			rev_rotate(stack);
		}
	}
	return ;
}

void	rotate_to_0_in_b(t_main_cont *cont, t_deque *curr_moves, int pos)
{
	if (pos < cont->stack_b.size - pos)
		while (pos-- > 0)
			do_rb(cont, curr_moves);
	else
		while (pos++ < cont->stack_b.size)
			do_rrb(cont, curr_moves);
	return ;
}
