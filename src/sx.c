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

void    do_sa(t_main_cont *cont, t_deque *moves_list)
{
	swap(&cont->stack_a);
	moves_list->add_last(moves_list, SA);

	swap_update_iterator(&cont->pos_min_val_a);
	swap_update_iterator(&cont->pos_max_val_a);

	if (DEBUG)
	{
		print_move(SA);
		print_stacks(cont);
		printf("%s\n", __FUNCTION__);
		print_stacks_info(cont);
	}

	return ;
}

void    do_sb(t_main_cont *cont, t_deque *moves_list)
{
	swap(&cont->stack_b);
	moves_list->add_last(moves_list, SB);

	swap_update_iterator(&cont->pos_min_val_b);
	swap_update_iterator(&cont->pos_max_val_b);

	if (DEBUG)
	{
		printf("%s\n", __FUNCTION__);
		print_move(SB);
		print_stacks(cont);
		print_stacks_info(cont);
	}

	return ;
}

void    do_ss(t_main_cont *cont, t_deque *moves_list)
{
	swap(&cont->stack_a);
	swap(&cont->stack_b);
	moves_list->add_last(moves_list, SS);

	swap_update_iterator(&cont->pos_min_val_a);
	swap_update_iterator(&cont->pos_max_val_a);
	swap_update_iterator(&cont->pos_min_val_b);
	swap_update_iterator(&cont->pos_max_val_b);

	if (DEBUG)
	{
		printf("%s\n", __FUNCTION__);
		print_move(SS);
		print_stacks(cont);
		print_stacks_info(cont);
	}

	return ;
}