#include "push_swap.h"

void	set_next_pos(int *pos, int size)
{
	if (*pos == size - 1)
		*pos = 0;
	else
		*pos += 1;
}

int	get_next_pos(int pos, int size)
{
	if (pos == size - 1)
		return (0);
	return (pos + 1);
}

//Get the pos in the stack of a given value. If not found (-1) is returned
int	get_stack_pos(int *stack, int size, int value)
{
	int	stack_pos;

	stack_pos = 0;
	while (stack_pos < size)
	{
		if (stack[stack_pos] == value)
			return (stack_pos);
		stack_pos++;
	}
	return (-1);
}