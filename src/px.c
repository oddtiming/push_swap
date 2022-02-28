#include "push_swap.h"

void	push(t_deque *stack_src, t_deque *stack_dest)
{
	stack_dest->add_front(stack_dest, stack_src->elems[0]);
	stack_src->remove_front(stack_src);
	return ;
}

static inline void	push_update_iterators(t_main_cont *cont)
{
	set_iterator(&cont->pos_min_val_a, get_pos_smallest_val(&cont->stack_a), cont->stack_a.nb_elems, CANONICAL);
	set_iterator(&cont->pos_max_val_a, get_pos_biggest_val(&cont->stack_a), cont->stack_a.nb_elems, CANONICAL);
	set_iterator(&cont->pos_min_val_b, get_pos_smallest_val(&cont->stack_b), cont->stack_b.nb_elems, REVERSE);
	set_iterator(&cont->pos_max_val_b, get_pos_biggest_val(&cont->stack_b), cont->stack_b.nb_elems, REVERSE);
	return ;
}

void    do_pa(t_main_cont *cont, t_deque *moves_list)
{
	push(&cont->stack_b, &cont->stack_a);
	if (moves_list)
		moves_list->add_last(moves_list, PA);
	
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

void    do_pb(t_main_cont *cont, t_deque *moves_list)
{
	push(&cont->stack_a, &cont->stack_b);
	if (moves_list)
		moves_list->add_last(moves_list, PB);
	
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
