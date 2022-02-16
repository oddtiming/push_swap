#include "push_swap.h"

int	*normalize_stack_values(int *src_stack, int size)
{
	int i;
	int	stack_pos;
	int	nb_smaller_elements;
	int	*normalized_stack;

	normalized_stack = malloc(size * sizeof(int));
	if (!normalized_stack)
		exit_on_err("Malloc error\n");
	stack_pos = 0;
	while (stack_pos < size)
	{
		i = 0;
		nb_smaller_elements = 0;
		while (i < size)
		{
			if (src_stack[i] < src_stack[stack_pos])
				nb_smaller_elements++;
			i++;
		}
		normalized_stack[stack_pos] = nb_smaller_elements;
		stack_pos++;
	}
	free(src_stack);
	return (normalized_stack);
}
