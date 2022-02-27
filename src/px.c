#include "push_swap.h"

void	push(t_vector *stack_src, t_vector *stack_dest)
{
	stack_dest->add_front(stack_dest, stack_src->elems[0]);
	stack_src->remove_front(stack_src);
	return ;
}

static inline void	push_update_iterators(t_main_cont *cont)
{
	set_iterator(&cont->pos_smallest_a, get_pos_smallest_val(&cont->stack_a), cont->stack_a.nb_elems, CANONICAL);
	set_iterator(&cont->pos_biggest_a, get_pos_biggest_val(&cont->stack_a), cont->stack_a.nb_elems, CANONICAL);
	set_iterator(&cont->pos_smallest_b, get_pos_smallest_val(&cont->stack_b), cont->stack_b.nb_elems, REVERSE);
	set_iterator(&cont->pos_biggest_b, get_pos_biggest_val(&cont->stack_b), cont->stack_b.nb_elems, REVERSE);
	return ;
}

void    do_pa(t_main_cont *cont, t_vector *moves_list)
{
	push(&cont->stack_b, &cont->stack_a);
	moves_list->add_back(moves_list, PA);
	push_update_iterators(cont);

	if (DEBUG)
	{
		printf("%s\n", __FUNCTION__);
		print_move(PA);
		print_stacks(cont);
		print_stacks_info(cont);
	}
	return ;
}

void    do_pb(t_main_cont *cont, t_vector *moves_list)
{
	push(&cont->stack_a, &cont->stack_b);
	moves_list->add_back(moves_list, PB);
	push_update_iterators(cont);

	if (DEBUG)
	{
		printf("%s\n", __FUNCTION__);
		print_move(PB);
		print_stacks(cont);
		print_stacks_info(cont);
	}
	return ;
}
