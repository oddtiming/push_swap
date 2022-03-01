#include "push_swap.h"

void	push(t_deque *stack_src, t_deque *stack_dest)
{
	stack_dest->add_front(stack_dest, stack_src->elems[0]);
	stack_src->remove_front(stack_src);
	return ;
}

static inline void	push_update_iterators(t_main_cont *cont)
{
	set_iterator(&cont->head_a, get_pos_smallest_val(&cont->stack_a), cont->stack_a.nb_elems, 0);
	set_iterator(&cont->tail_a, get_pos_biggest_val(&cont->stack_a), cont->stack_a.nb_elems, 0);
	set_iterator(&cont->head_b, get_pos_smallest_val(&cont->stack_b), cont->stack_b.nb_elems, 1);
	set_iterator(&cont->tail_b, get_pos_biggest_val(&cont->stack_b), cont->stack_b.nb_elems, 1);
	return ;
}

void    do_pa(t_main_cont *cont, t_deque *temp_moves)
{
	push(&cont->stack_b, &cont->stack_a);
	if (temp_moves)
		temp_moves->add_last(temp_moves, PA);
	
	push_update_iterators(cont);

	if (DEBUG)
	{
		printf("%s\n", __FUNCTION__);
		print_move(PA);
		print_stacks(cont);
	}
	
	return ;
}

void    do_pb(t_main_cont *cont, t_deque *temp_moves)
{
	push(&cont->stack_a, &cont->stack_b);
	if (temp_moves)
		temp_moves->add_last(temp_moves, PB);
	
	push_update_iterators(cont);

	if (DEBUG)
	{
		printf("%s\n", __FUNCTION__);
		print_move(PB);
		print_stacks(cont);
	}
	
	return ;
}
