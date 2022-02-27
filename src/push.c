#include "push_swap.h"

void	push(t_vector *stack_src, t_vector *stack_dest)
{
	stack_dest->add_front(stack_dest, stack_src->list.elems[0]);
	stack_src->remove_front(stack_src);
	return ;
}


void    do_push(t_main_cont *cont, t_vector *moves_list, int move)
{
	if ((move & 0xFF) == 'a')
		push(&cont->stack_b, &cont->stack_a);
	else if ((move & 0xFF) == 'b')
		push(&cont->stack_a, &cont->stack_b);
	moves_list->add_back(moves_list, move);
	if (DEBUG)
	{
		print_move(move);
		print_stacks(cont);
	}
	return ;
}
