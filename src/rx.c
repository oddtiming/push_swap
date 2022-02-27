#include "push_swap.h"

void	rotate(t_vector *stack)
{
	int	temp;

	temp = stack->elems[0];
	stack->remove_front(stack);
	stack->add_back(stack, temp);
	return ;
}

static inline void	rotate_update_iterators(t_iterator *iterator)
{
	iterate_once(iterator, REVERSE);
	return ;
}

void    do_ra(t_main_cont *cont, t_vector *moves_list)
{
	rotate(&cont->stack_a);
	moves_list->add_back(moves_list, RA);

	rotate_update_iterators(&cont->pos_smallest_a);
	rotate_update_iterators(&cont->pos_biggest_a);

	if (DEBUG)
	{
		print_move(RA);
		print_stacks(cont);
		print_stacks_info(cont);
	}

	return ;
}

void    do_rb(t_main_cont *cont, t_vector *moves_list)
{
	rotate(&cont->stack_b);
	moves_list->add_back(moves_list, RB);

	rotate_update_iterators(&cont->pos_smallest_b);
	rotate_update_iterators(&cont->pos_biggest_b);

	if (DEBUG)
	{
		print_move(RB);
		print_stacks(cont);
		print_stacks_info(cont);
	}

	return ;
}

void	do_rr(t_main_cont *cont, t_vector *moves_list)
{
	rotate(&cont->stack_a);
	rotate(&cont->stack_b);
	moves_list->add_back(moves_list, RR);

	rotate_update_iterators(&cont->pos_smallest_a);
	rotate_update_iterators(&cont->pos_biggest_a);
	rotate_update_iterators(&cont->pos_smallest_b);
	rotate_update_iterators(&cont->pos_biggest_b);

	if (DEBUG)
	{
		print_move(RR);
		print_stacks(cont);
		print_stacks_info(cont);
	}	

	return ;
}
