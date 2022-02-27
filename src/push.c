#include "push_swap.h"

void	push(t_vector *stack_src, t_vector *stack_dest)
{
	stack_dest->add_front(stack_dest, stack_src->elems[0]);
	stack_src->remove_front(stack_src);
	return ;
}


void    do_pa(t_main_cont *cont, t_vector *moves_list)
{
	int	prev_smallest_in_a;
	int	prev_biggest_in_a;

	prev_smallest_in_a = cont->pos_smallest_a.index;
	prev_biggest_in_a = cont->pos_biggest_a.index;
	push(&cont->stack_b, &cont->stack_a);
	moves_list->add_back(moves_list, PA);
	if (cont->stack_a.elems[0] < prev_smallest_in_a)
		set_iterator(&cont->pos_smallest_b, cont->stack_b.smallest_elem, cont->stack_b.nb_elems, CANONICAL);
	if (cont->stack_a.elems[0] > prev_biggest_in_a)
		set_iterator(&cont->pos_biggest_b, cont->stack_b.biggest_elem, cont->stack_b.nb_elems, CANONICAL);
	if (DEBUG)
	{
		print_move(PA);
		print_stacks(cont);
	}
	return ;
}

void    do_pb(t_main_cont *cont, t_vector *moves_list)
{
	int	prev_smallest_in_b;
	int	prev_biggest_in_b;

	prev_smallest_in_b = cont->pos_smallest_b.index;
	prev_biggest_in_b = cont->pos_biggest_b.index;
	push(&cont->stack_a, &cont->stack_b);
	moves_list->add_back(moves_list, PB);
	if (cont->stack_b.elems[0] < prev_smallest_in_b)
		set_iterator(&cont->pos_smallest_a, cont->stack_a.smallest_elem, cont->stack_a.nb_elems, CANONICAL);
	if (cont->stack_b.elems[0] > prev_biggest_in_b)
		set_iterator(&cont->pos_biggest_a, cont->stack_a.biggest_elem, cont->stack_a.nb_elems, CANONICAL);
	if (DEBUG)
	{
		print_move(PB);
		print_stacks(cont);
	}
	return ;
}
