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

t_deque	*get_staying_vals(t_deque *stack)
{
	t_deque	**list;
	t_deque	*staying_vals;
	int		list_size;
	int		i;
	int		j;

	list = malloc(stack->max_elem * sizeof(t_deque *));
	ft_bzero(list, stack->max_elem);
	new_deque(&list[0]);
	list[0]->add_last(list[0], stack->elems[0]);
	list[1] = NULL;
	i = 1;
	list_size = 1;
	while (i < stack->size)
	{
		// If it's larger than the current largest, clone and extend
		if (stack->elems[i] > list[list_size - 1]->max_elem)
		{
			new_deque(&list[list_size]);
			copy_deque(list[list_size - 1], list[list_size]);
			list[list_size]->add_last(list[list_size], stack->elems[i]);
			// printf(YELLOW"new_biggest\n"RESET_COL);
			// print_single_stack(list[list_size]);
			list_size++;
		}
		// Find the deque where max_elem < curr_value, clone, extend, and discard
		else
		{
			j = list_size - 1;
			while (j >= 0)
			{
				if (list[j]->max_elem < stack->elems[i])
				{
					//I'm making the observation that you seem to always delete the one after
					copy_deque(list[j], list[j + 1]);
					list[j + 1]->add_last(list[j + 1], stack->elems[i]);
					// printf(MAGENTA"new insert for j = %d \n"RESET_COL, j);
					// print_single_stack(list[j + 1]);
					break;
				}
				j--;
			}
		}
		i++;
	}
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
