#include "push_swap.h"

int	get_pos_smallest_value(t_vector *stack)
{
	int	pos_in_stack;

	pos_in_stack = 0;
	if (stack->list.nb_elems == 0)
		return (0);
	while (stack->list.elems[pos_in_stack] != stack->list.smallest_elem)
		pos_in_stack++;
	return (pos_in_stack);
}

int	get_pos_biggest_value(t_vector *stack)
{
	int	pos_in_stack;

	pos_in_stack = 0;
	if (stack->list.nb_elems == 0)
		return (0);
	while (stack->list.elems[pos_in_stack] != stack->list.biggest_elem)
		pos_in_stack++;
	return (pos_in_stack);
}

int	is_sorted_at_pos(t_vector *stack)
{
	t_iterator	iterator;
	int			*elems;
	int			pos_smallest;
	int			size;
	int			nb_sorted;

	nb_sorted = 1;
	pos_smallest = get_pos_smallest_value(stack);
	size = stack->list.nb_elems;
	elems = stack->list.elems;
	set_iterator(&iterator, pos_smallest, size, CANONICAL);
	while (iterate_one_loop(&iterator))
	{
		if (elems[iterator.index] > elems[iterator.prev_index])
			nb_sorted++;
	}
	if (DEBUG)
		printf("nb_sorted at %d == %d\n", pos_smallest, nb_sorted);
	if (nb_sorted == size)
		return (pos_smallest);
	return (-1);
}

void	rotate_pos_in_a_to_0(t_main_cont *cont, t_vector *moves_list, int pos)
{
	if (pos < cont->stack_a.list.nb_elems - pos)
		while (pos-- > 0)
			do_rotate(cont, moves_list, RA);
	else
		while (pos++ < cont->stack_a.list.nb_elems)
			do_rev_rotate(cont, moves_list, RRA);
	return ;
}

void	rotate_pos_in_b_to_0(t_main_cont *cont, t_vector *moves_list, int pos)
{
	if (pos < cont->stack_b.list.nb_elems - pos)
		while (pos-- > 0)
			do_rotate(cont, moves_list, RB);
	else
		while (pos++ < cont->stack_b.list.nb_elems)
			do_rev_rotate(cont, moves_list, RRB);
	return ;
}
