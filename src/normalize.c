#include "push_swap.h"

int	*normalize_stack_values(int *src_stack, int size)
{
	int i;
	int	pos_in_stack;
	int	nb_smaller_elements;
	int	*normalized_stack;

	normalized_stack = malloc(size * sizeof(int));
	if (!normalized_stack)
		exit_on_err("Malloc error\n");
	pos_in_stack = 0;
	while (pos_in_stack < size)
	{
		i = 0;
		nb_smaller_elements = 0;
		while (i < size)
		{
			if (src_stack[i] < src_stack[pos_in_stack])
				nb_smaller_elements++;
			i++;
		}
		normalized_stack[pos_in_stack] = nb_smaller_elements;
		pos_in_stack++;
	}
	src_stack = ft_memcpy(src_stack, normalized_stack, size * sizeof(int));
	free(normalized_stack);
	return (src_stack);
}
