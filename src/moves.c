#include "push_swap.h"

void	rotate(t_vector *stack)
{
	int	temp;

	temp = stack->get_elem(stack, 0);
	stack->remove_front(stack);
	stack->add_back(stack, temp);
	return ;
}

void	rev_rotate(t_vector *stack)
{
	int	temp;

	temp = stack->get_elem(stack, stack->list.nb_elems - 1);
	stack->remove_back(stack);
	stack->add_front(stack, temp);
	return ;
}

void	swap(t_vector *stack)
{
	int	temp;

	temp = stack->get_elem(stack, 0);
	stack->set_elem(stack, 0, stack->get_elem(stack, 1));
	stack->set_elem(stack, 1, temp);
	return ;
}

void	push(t_vector *stack_src, t_vector *stack_dest)
{
	stack_dest->add_front(stack_src->get_elem(stack_src, 0));
	stack_src->remove_front(stack_src);
	return ;
}