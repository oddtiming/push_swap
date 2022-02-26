#include "push_swap.h"

void	rev_rotate(t_vector *stack)
{
	int	temp;

	temp = stack->get_elem(stack, stack->list.nb_elems - 1);
	stack->remove_back(stack);
	stack->add_front(stack, temp);
	return ;
}

void    do_rev_rotate(t_main_cont *cont, t_vector *moves_list, int move)
{
	if ((move & 0xFF) == 'a' || (move & 0xFF) == 'r')
		rev_rotate(&cont->stack_a);
	if ((move & 0xFF) == 'b' || (move & 0xFF) == 'r')
		rev_rotate(&cont->stack_b);
	moves_list->add_back(moves_list, move);
	if (DEBUG)
	{
		print_move(move);
		print_stacks(cont);
	}
	return ;
}
