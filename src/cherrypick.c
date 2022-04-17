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

void	free_deque_list(t_deque **list)
{
	int	i;

	i = 0;
	while (list[i + 1] != NULL)
	{
		list[i]->free_list(list[i]);
		free (list[i]);
		i++;
	}
	free (list);
	return ;
}

int	longest_increasing_subsequence(t_deque **list, t_deque *stack)
{
	int		list_size;
	int		i;
	int		j;

	i = 0;
	list_size = 1;
	while (++i < stack->size)
	{
		if (stack->elems[i] > list[list_size - 1]->max_elem)
		{
			list[list_size] = clone_deque(list[list_size - 1]);
			// new_deque(&list[list_size]);
			// copy_deque(list[list_size - 1], list[list_size]);
			list[list_size]->add_last(list[list_size], stack->elems[i]);
			list_size++;
		}
		else
		{
			j = list_size - 1;
			while (list[j]->max_elem > stack->elems[i] && j >= 0)
				j--;
			copy_deque(list[j], list[j + 1]);
			list[j + 1]->add_last(list[j + 1], stack->elems[i]);
		}
	}
	return (list_size);
}

t_deque	*get_ordered_vals(t_deque *stack)
{
	t_deque	**list;
	t_deque	*staying_vals;
	int		list_size;
	int		i;

	list = ft_safealloc(stack->max_elem * sizeof(t_deque *));
	ft_bzero(list, stack->max_elem);
	new_deque(&list[0]);
	list[0]->add_last(list[0], stack->elems[0]);
	list_size = longest_increasing_subsequence(list, stack);
	staying_vals = list[list_size - 1];
	i = 0;
	while (i < list_size - 1)
	{
		list[i]->free_list(list[i]);
		free (list[i]);
		i++;
	}
	free(list);
	return (staying_vals);
}
