#include "push_swap.h"

int	get_pos_of_val(t_deque *stack, int val)
{
	int	pos;

	pos = 0;
	while (pos < stack->nb_elems)
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
	if (stack->nb_elems == 0)
		return (0);
	while (stack->elems[pos_in_stack] != stack->elem_min)
		pos_in_stack++;
	return (pos_in_stack);
}

int	get_pos_biggest_val(t_deque *stack)
{
	int	pos_in_stack;

	pos_in_stack = 0;
	if (stack->nb_elems == 0)
		return (0);
	while (stack->elems[pos_in_stack] != stack->elem_max)
		pos_in_stack++;
	return (pos_in_stack);
}

int		get_next_bigger(t_deque *stack, int curr_val)
{
	int	pos;
	int	next_bigger;

	if (curr_val + 1 > stack->elem_max)
		return (stack->elem_min);
	next_bigger = curr_val + 1;
	pos = 0;
	while (pos < stack->nb_elems)
	{
		if (stack->elems[pos] == next_bigger)
			return (next_bigger);
		pos++;
	}
	return (get_next_bigger(stack, next_bigger + 1));
}

//Since the pos_smallest lives outside the deque (that's really dumb btw),
//pos_smallest needs to be passed as a parameter for now. Should change it soon
//	Returns true if sorted 
//	Returns false if not sorted 
bool	is_sorted(t_deque *stack, int pos_smallest)
{
	t_iterator	iter;

	set_iterator(&iter, pos_smallest, stack->nb_elems, 0);
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
 * rotations made to moves_list
 * 
 * @param cont 			main container
 * @param moves_list 	moves to which rotations will be added
 * @param pos 			pos to be rotated to pos_0
 */
void	rotate_pos_in_a_to_0(t_main_cont *cont, t_deque *moves_list, int pos)
{
	if (pos < cont->stack_a.nb_elems - pos)
		while (pos-- > 0)
			do_ra(cont, moves_list);
	else
		while (pos++ < cont->stack_a.nb_elems)
			do_rra(cont, moves_list);
	return ;
}

void	rotate_pos_in_b_to_0(t_main_cont *cont, t_deque *moves_list, int pos)
{
	if (pos < cont->stack_b.nb_elems - pos)
		while (pos-- > 0)
			do_rb(cont, moves_list);
	else
		while (pos++ < cont->stack_b.nb_elems)
			do_rrb(cont, moves_list);
	return ;
}

// void	insert_b(t_main_cont *cont)
// {
// 	t_deque	*best_moves_list;

// 	best_moves_list = malloc(sizeof(t_deque));

// }