#include "push_swap.h"

void	rev_rotate(t_vector *stack)
{
	int	temp;

	temp = stack->elems[stack->nb_elems - 1];
	stack->remove_back(stack);
	stack->add_front(stack, temp);
	return ;
}

void    do_rra(t_main_cont *cont, t_vector *moves_list)
{
	rev_rotate(&cont->stack_a);
	moves_list->add_back(moves_list, RRA);
	iterate_once(&cont->pos_smallest_a, CANONICAL);
	iterate_once(&cont->pos_biggest_a, CANONICAL);
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
	iterate_once(&cont->pos_smallest_b, CANONICAL);
	iterate_once(&cont->pos_biggest_b, CANONICAL);
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
	iterate_once(&cont->pos_smallest_b, CANONICAL);
	iterate_once(&cont->pos_biggest_b, CANONICAL);
	iterate_once(&cont->pos_smallest_a, CANONICAL);
	iterate_once(&cont->pos_biggest_a, CANONICAL);
	rev_rotate(&cont->stack_a);
	rev_rotate(&cont->stack_b);
	moves_list->add_back(moves_list, RRR);
	if (DEBUG)
	{
		print_move(RRR);
		print_stacks(cont);
		print_stacks_info(cont);
	}	
	return ;
}
