#include "push_swap.h"

void	copy_deque(t_deque *src, t_deque *dest)
{
	int	i;

	dest->reinit_list(dest);
	if (!src)
		return ;			
	i = 0;
	while (i < src->size)
	{
		dest->add_last(dest, src->elems[i]);
		i++;
	}
	return ;
}

void	cat_deque(t_deque *src, t_deque *dest)
{
	int	i;

	if (!src)
		return ;		
	i = 0;
	while (i < src->size)
	{
		dest->add_last(dest, src->elems[i]);
		i++;
	}
	return ;
}

void	cat_deque_front(t_deque *src, t_deque *dest)
{
	int	i;

	if (!src)
		return ;		
	i = src->size - 1;
	while (i >= 0)
	{
		dest->add_front(dest, src->elems[i]);
		i--;
	}
	return ;
}
