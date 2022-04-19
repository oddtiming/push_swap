#include "push_swap.h"

bool	is_in_stack(t_deque *stack, int val)
{
	int	i;
	i = 0;
	while (i < stack->size)
	{
		if (stack->elems[i] == val)
			return (true);
		i++;
	}
	return (false);
}

void	free_deque_list(t_deque **list, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		list[i]->free_list(list[i]);
		free (list[i]);
		i++;
	}
	free (list);
	return ;
}
