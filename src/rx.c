#include "push_swap.h"

void	rotate(t_deque *stack)
{
	int	temp;

	temp = stack->elems[0];
	stack->remove_front(stack);
	stack->add_last(stack, temp);
	return ;
}

static inline void	rotate_update_iterators(t_iterator *iterator)
{
	iterate_once(iterator, 1);
	return ;
}

void    do_ra(t_main_cont *cont, t_deque *curr_moves)
{
	rotate(&cont->stack_a);
	if (curr_moves)
		curr_moves->add_last(curr_moves, RA);

	rotate_update_iterators(&cont->head_a);

	if (DEBUG)
	{
		print_move(RA);
		// print_stacks(cont);
	}

	return ;
}

void    do_rb(t_main_cont *cont, t_deque *curr_moves)
{
	rotate(&cont->stack_b);
	if (curr_moves)
		curr_moves->add_last(curr_moves, RB);

	rotate_update_iterators(&cont->head_b);

	if (DEBUG)
	{
		print_move(RB);
		// print_stacks(cont);
	}

	return ;
}

void	do_rr(t_main_cont *cont, t_deque *curr_moves)
{
	rotate(&cont->stack_a);
	rotate(&cont->stack_b);
	if (curr_moves)
		curr_moves->add_last(curr_moves, RR);

	rotate_update_iterators(&cont->head_a);
	rotate_update_iterators(&cont->head_b);

	if (DEBUG)
	{
		print_move(RR);
		// print_stacks(cont);
	}	

	return ;
}
