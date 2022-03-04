#include "push_swap.h"


int ft_max(int a, int b)
{
	return ((a >= b) * a + (b > a) * b);
}

int ft_min(int a, int b)
{
	return ((a <= b) * a + (b < a) * b);
}

int ft_abs(int a)
{
	return ((a >= 0) * a + (a < 0) * (-a));
}

bool	ft_same_sign(int a, int b)
{
	return ((a >= 0 && b >= 0) || ((a < 0) && (b < 0)));
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
