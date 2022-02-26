#include "push_swap.h"

void	swap(t_vector *stack)
{
	int	temp;

	temp = stack->get_elem(stack, 0);
	stack->set_elem(stack, 0, stack->get_elem(stack, 1));
	stack->set_elem(stack, 1, temp);
	return ;
}

void    do_swap(t_main_cont *cont, t_vector *moves_list, int move)
{
	if ((move & 0xFF) == 'a' || (move & 0xFF) == 's')
		swap(&cont->stack_a);
	if ((move & 0xFF) == 'b' || (move & 0xFF) == 's')
		swap(&cont->stack_b);
	moves_list->add_back(moves_list, move);
	if (DEBUG)
	{
		print_move(move);
		print_stacks(cont);
	}
	return ;
}
