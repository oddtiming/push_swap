#include "push_swap.h"

void	rotate(t_vector *stack)
{
	int	temp;

	temp = stack->get_elem(stack, 0);
	stack->remove_front(stack);
	stack->add_back(stack, temp);
	return ;
}
