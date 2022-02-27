#include "push_swap.h"

void	rotate(t_vector *stack)
{
	int	temp;

	temp = stack->elems[0];
	stack->remove_front(stack);
	stack->add_back(stack, temp);
	return ;
}

void    do_ra(t_main_cont *cont, t_vector *moves_list)
{
	// set_iterator(&cont->pos_biggest_a, cont->pos_biggest_a.index, cont->stack_a.nb_elems, CANONICAL);
	rotate(&cont->stack_a);
	moves_list->add_back(moves_list, RA);
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
	if (DEBUG)
	{
		print_move(RB);
		print_stacks(cont);
		print_stacks_info(cont);
	}
	return ;
}



	// if ((move & 0xFF) == 'a' || (move & 0xFF) == 'r')
	// if ((move & 0xFF) == 'b' || (move & 0xFF) == 'r')
	// 	rotate(&cont->stack_b);