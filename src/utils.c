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
int	get_pos_in_stack(int *stack, int size, int value)
{
	int	pos_in_stack;

	pos_in_stack = 0;
	while (pos_in_stack < size)
	{
		if (stack[pos_in_stack] == value)
			return (pos_in_stack);
		pos_in_stack++;
	}
	return (-1);
}

#define MALLOC_SUCCESS 0
#define MALLOC_FAILURE 1

bool	ft_assign_calloc(void **ptr, size_t count, size_t size)
{
	ptr = malloc(count * size);
	if (!ptr)
	{
		ptr = NULL;
		return (MALLOC_FAILURE);
	}
	ft_bzero(ptr, size);
	return (MALLOC_SUCCESS);
}