#include "push_swap.h"

void	rotate(t_vector *stack)
{
	int	temp;

	temp = stack->list.elems[0];
	stack->remove_front(stack);
	stack->add_back(stack, temp);
	return ;
}

void    do_rotate(t_main_cont *cont, t_vector *moves_list, int move)
{
	if ((move & 0xFF) == 'a' || (move & 0xFF) == 'r')
		rotate(&cont->stack_a);
	if ((move & 0xFF) == 'b' || (move & 0xFF) == 'r')
		rotate(&cont->stack_b);
	moves_list->add_back(moves_list, move);
	if (DEBUG)
	{
		print_move(move);
		print_stacks(cont);
	}
	return ;
}
