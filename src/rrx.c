#include "push_swap.h"

void	rev_rotate(t_vector *stack)
{
	int	temp;

	temp = stack->elems[stack->nb_elems - 1];
	stack->remove_back(stack);
	stack->add_front(stack, temp);
	return ;
}

static inline void	rev_rotate_update_iterators(t_iterator *iterator)
{
	iterate_once(iterator, CANONICAL);
	return ;
}

void    do_rra(t_main_cont *cont, t_vector *moves_list)
{
	rev_rotate(&cont->stack_a);
	moves_list->add_back(moves_list, RRA);

	rev_rotate_update_iterators(&cont->pos_smallest_a);
	rev_rotate_update_iterators(&cont->pos_biggest_a);

	if (DEBUG)
	{
		print_move(RRA);
		print_stacks(cont);
		print_stacks_info(cont);
	}
	
	return ;
}

void    do_rrb(t_main_cont *cont, t_vector *moves_list)
{
	rev_rotate(&cont->stack_b);
	moves_list->add_back(moves_list, RRB);

	rev_rotate_update_iterators(&cont->pos_smallest_b);
	rev_rotate_update_iterators(&cont->pos_biggest_b);

	if (DEBUG)
	{
		print_move(RRB);
		print_stacks(cont);
		print_stacks_info(cont);
	}
	
	return ;
}

void	do_rrr(t_main_cont *cont, t_vector *moves_list)
{
	rev_rotate(&cont->stack_a);
	rev_rotate(&cont->stack_b);
	moves_list->add_back(moves_list, RRR);

	rev_rotate_update_iterators(&cont->pos_smallest_b);
	rev_rotate_update_iterators(&cont->pos_biggest_b);
	rev_rotate_update_iterators(&cont->pos_smallest_a);
	rev_rotate_update_iterators(&cont->pos_biggest_a);

	if (DEBUG)
	{
		print_move(RRR);
		print_stacks(cont);
		print_stacks_info(cont);
	}	
	
	return ;
}
