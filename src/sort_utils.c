#include "push_swap.h"

int	get_pos_smallest_val(t_vector *stack)
{
	int	pos_in_stack;

	pos_in_stack = 0;
	if (stack->nb_elems == 0)
		return (0);
	while (stack->elems[pos_in_stack] != stack->smallest_elem)
		pos_in_stack++;
	return (pos_in_stack);
}

int	get_pos_biggest_val(t_vector *stack)
{
	int	pos_in_stack;

	pos_in_stack = 0;
	if (stack->nb_elems == 0)
		return (0);
	while (stack->elems[pos_in_stack] != stack->biggest_elem)
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
	pos_smallest = get_pos_smallest_val(stack);
	size = stack->nb_elems;
	elems = stack->elems;
	set_iterator(&iterator, pos_smallest, size, CANONICAL);
	while (iterate_n_loops(&iterator, 1))
	{
		if (elems[iterator.index] > elems[iterator.prev_index])
			nb_sorted++;
	}
	if (nb_sorted == size)
		return (pos_smallest);
	return (-1);
}

void	rotate_pos_in_a_to_0(t_main_cont *cont, t_vector *moves_list, int pos)
{
	if (pos < cont->stack_a.nb_elems - pos)
		while (pos-- > 0)
			do_ra(cont, moves_list);
	else
		while (pos++ < cont->stack_a.nb_elems)
			do_rra(cont, moves_list);
	return ;
}

void	rotate_pos_in_b_to_0(t_main_cont *cont, t_vector *moves_list, int pos)
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
// 	t_vector	*best_moves_list;

// 	best_moves_list = malloc(sizeof(t_vector));

// }