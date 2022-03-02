#include "push_swap.h"

void	rev_rotate(t_deque *stack)
{
	int	temp;

	temp = stack->elems[stack->nb_elems - 1];
	stack->remove_last(stack);
	stack->add_front(stack, temp);
	return ;
}

static inline void	rev_rotate_update_iterators(t_iterator *iterator)
{
	iterate_once(iterator, 0);
	return ;
}

void    do_rra(t_main_cont *cont, t_deque *curr_moves)
{
	rev_rotate(&cont->stack_a);
	if (curr_moves)
		curr_moves->add_last(curr_moves, RRA);

	rev_rotate_update_iterators(&cont->head_a);
	rev_rotate_update_iterators(&cont->tail_a);

	if (DEBUG)
	{
		print_move(RRA);
		print_stacks(cont);
	}
	
	return ;
}

void    do_rrb(t_main_cont *cont, t_deque *curr_moves)
{
	rev_rotate(&cont->stack_b);
	if (curr_moves)
		curr_moves->add_last(curr_moves, RRB);

	rev_rotate_update_iterators(&cont->head_b);
	rev_rotate_update_iterators(&cont->tail_b);

	if (DEBUG)
	{
		print_move(RRB);
		print_stacks(cont);
	}
	
	return ;
}

void	do_rrr(t_main_cont *cont, t_deque *curr_moves)
{
	rev_rotate(&cont->stack_a);
	rev_rotate(&cont->stack_b);
	if (curr_moves)
		curr_moves->add_last(curr_moves, RRR);

	rev_rotate_update_iterators(&cont->head_b);
	rev_rotate_update_iterators(&cont->tail_b);
	rev_rotate_update_iterators(&cont->head_a);
	rev_rotate_update_iterators(&cont->tail_a);

	if (DEBUG)
	{
		print_move(RRR);
		print_stacks(cont);
	}	
	
	return ;
}
