#include "push_swap.h"

void	set_next_index(int *index, int size)
{
	if (*index == size - 1)
		*index = 0;
	else
		*index += 1;
}
