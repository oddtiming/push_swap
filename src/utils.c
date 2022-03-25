#include "push_swap.h"

void	*ft_safealloc(size_t size)
{
	void	*mem_space;

	mem_space = malloc(size);
	if (!mem_space)
	{
		write(STDERR_FILENO, "Malloc Error\n", 13);
		exit (EXIT_FAILURE);
	}
	return (mem_space);
}

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
