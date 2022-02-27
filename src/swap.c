#include "push_swap.h"

void	swap(t_vector *stack)
{
	int	temp;

	temp = stack->elems[0];
	stack->set_elem(stack, 0, stack->elems[1]);
	stack->set_elem(stack, 1, temp);
	return ;
}

void    do_sa(t_main_cont *cont, t_vector *moves_list)
{
	if (cont->pos_smallest_a.index == 0 || cont->pos_smallest_a.index == 1)
		iterate_once(&cont->pos_smallest_a, cont->pos_smallest_a.index);
	if (cont->pos_biggest_a.index == 0 || cont->pos_biggest_a.index == 1)
		iterate_once(&cont->pos_biggest_a, cont->pos_biggest_a.index);
	swap(&cont->stack_a);
	moves_list->add_back(moves_list, SA);
	if (DEBUG)
	{
		print_move(SA);
		print_stacks(cont);
		printf("%s\n", __FUNCTION__);
		print_stacks_info(cont);
	}
	return ;
}

void    do_sb(t_main_cont *cont, t_vector *moves_list)
{
	if (cont->pos_smallest_b.index == 0 || cont->pos_smallest_b.index == 1)
		iterate_once(&cont->pos_smallest_b, cont->pos_smallest_b.index);
	if (cont->pos_biggest_b.index == 0 || cont->pos_biggest_b.index == 1)
		iterate_once(&cont->pos_biggest_b, cont->pos_biggest_b.index);
	swap(&cont->stack_b);
	moves_list->add_back(moves_list, SB);
	if (DEBUG)
	{
		printf("%s\n", __FUNCTION__);
		print_move(SB);
		print_stacks(cont);
		print_stacks_info(cont);
	}
	return ;
}

void    do_ss(t_main_cont *cont, t_vector *moves_list)
{
	if (cont->pos_smallest_a.index == 0 || cont->pos_smallest_a.index == 1)
		iterate_once(&cont->pos_smallest_a, cont->pos_smallest_a.index);
	if (cont->pos_biggest_a.index == 0 || cont->pos_biggest_a.index == 1)
		iterate_once(&cont->pos_biggest_a, cont->pos_biggest_a.index);
	if (cont->pos_smallest_b.index == 0 || cont->pos_smallest_b.index == 1)
		iterate_once(&cont->pos_smallest_b, cont->pos_smallest_b.index);
	if (cont->pos_biggest_b.index == 0 || cont->pos_biggest_b.index == 1)
		iterate_once(&cont->pos_biggest_b, cont->pos_biggest_b.index);
	swap(&cont->stack_a);
	swap(&cont->stack_b);
	moves_list->add_back(moves_list, SS);
	if (DEBUG)
	{
		printf("%s\n", __FUNCTION__);
		print_move(SS);
		print_stacks(cont);
		print_stacks_info(cont);
	}
	return ;
}
