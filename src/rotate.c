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
	rotate(&cont->stack_a);
	moves_list->add_back(moves_list, RA);
	iterate_once(&cont->pos_smallest_a, REVERSE);
	iterate_once(&cont->pos_biggest_a, REVERSE);
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
	iterate_once(&cont->pos_smallest_b, REVERSE);
	iterate_once(&cont->pos_biggest_b, REVERSE);
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
	iterate_once(&cont->pos_smallest_a, REVERSE);
	iterate_once(&cont->pos_biggest_a, REVERSE);
	iterate_once(&cont->pos_smallest_b, REVERSE);
	iterate_once(&cont->pos_biggest_b, REVERSE);
	if (DEBUG)
	{
		print_move(RR);
		print_stacks(cont);
		print_stacks_info(cont);
	}	
	return ;
}
