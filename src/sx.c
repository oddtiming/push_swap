#include "push_swap.h"

void	swap(t_deque *stack)
{
	int	temp;

	temp = stack->elems[0];
	stack->set_elem(stack, 0, stack->elems[1]);
	stack->set_elem(stack, 1, temp);
	return ;
}

static inline void	swap_update_iterator(t_iterator *iterator)
{
	if (iterator->index == 0 || iterator->index == 1)
		iterate_once(iterator, iterator->index);
	return ;
}

void    do_sa(t_main_cont *cont, t_deque *curr_moves)
{
	swap(&cont->stack_a);
	if (curr_moves)
		curr_moves->add_last(curr_moves, SA);

	swap_update_iterator(&cont->head_a);
	swap_update_iterator(&cont->tail_a);

	if (DEBUG)
	{
		print_move(SA);
		print_stacks(cont);
		printf("%s\n", __FUNCTION__);
	}

	return ;
}

void    do_sb(t_main_cont *cont, t_deque *curr_moves)
{
	swap(&cont->stack_b);
	if (curr_moves)
		curr_moves->add_last(curr_moves, SB);

	swap_update_iterator(&cont->head_b);
	swap_update_iterator(&cont->tail_b);

	if (DEBUG)
	{
		printf("%s\n", __FUNCTION__);
		print_move(SB);
		print_stacks(cont);
	}

	return ;
}

void    do_ss(t_main_cont *cont, t_deque *curr_moves)
{
	swap(&cont->stack_a);
	swap(&cont->stack_b);
	if (curr_moves)
		curr_moves->add_last(curr_moves, SS);

	swap_update_iterator(&cont->head_a);
	swap_update_iterator(&cont->tail_a);
	swap_update_iterator(&cont->head_b);
	swap_update_iterator(&cont->tail_b);

	if (DEBUG)
	{
		printf("%s\n", __FUNCTION__);
		print_move(SS);
		print_stacks(cont);
	}

	return ;
}