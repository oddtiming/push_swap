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
	iterate_once(iterator, CANONICAL);
	return ;
}

void    do_rra(t_main_cont *cont, t_deque *moves_list)
{
	rev_rotate(&cont->stack_a);
	if (moves_list)
		moves_list->add_last(moves_list, RRA);

	rev_rotate_update_iterators(&cont->pos_min_val_a);
	rev_rotate_update_iterators(&cont->pos_max_val_a);

	if (DEBUG)
	{
		print_move(RRA);
		print_stacks(cont);
		print_stacks_info(cont);
	}
	
	return ;
}

void    do_rrb(t_main_cont *cont, t_deque *moves_list)
{
	rev_rotate(&cont->stack_b);
	if (moves_list)
		moves_list->add_last(moves_list, RRB);

	rev_rotate_update_iterators(&cont->pos_min_val_b);
	rev_rotate_update_iterators(&cont->pos_max_val_b);

	if (DEBUG)
	{
		print_move(RRB);
		print_stacks(cont);
		print_stacks_info(cont);
	}
	
	return ;
}

void	do_rrr(t_main_cont *cont, t_deque *moves_list)
{
	rev_rotate(&cont->stack_a);
	rev_rotate(&cont->stack_b);
	if (moves_list)
		moves_list->add_last(moves_list, RRR);

	rev_rotate_update_iterators(&cont->pos_min_val_b);
	rev_rotate_update_iterators(&cont->pos_max_val_b);
	rev_rotate_update_iterators(&cont->pos_min_val_a);
	rev_rotate_update_iterators(&cont->pos_max_val_a);

	if (DEBUG)
	{
		print_move(RRR);
		print_stacks(cont);
		print_stacks_info(cont);
	}	
	
	return ;
}
