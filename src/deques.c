#include "push_swap.h"

void init_deque(t_deque *deque)
{
	//Add the atrocious list of helper functions(probs too much)
	deque->add_front	= &deque_add_front;
	deque->add_last		= &deque_add_last;
	deque->free_list	= &deque_free_list;
	deque->get_elem_max	= &deque_get_elem_max;
	deque->get_elem_min	= &deque_get_elem_min;
	deque->reinit_list	= &deque_reinit_list;
	deque->remove_front	= &deque_remove_front;
	deque->remove_last	= &deque_remove_last;
	deque->resize_end	= &deque_resize_end;
	deque->resize_front	= &deque_resize_front;
	deque->set_elem		= &deque_set_elem;


	//Malloc a block of memory designed to leave space on each side of the
	//deque_head, so that values can be added on both ends with the same
	//calculation cost, and there is still a single memory space.
	deque->nb_elems			= 0;
	deque->elem_min			= deque->get_elem_min(deque);
	deque->elem_max			= deque->get_elem_max(deque);
	deque->capacity_end		= VECTOR_INIT_SIZE;
	deque->capacity_front	= VECTOR_INIT_SIZE;
	deque->capacity_total	= 2 * VECTOR_INIT_SIZE;
	deque->malloced_space	= malloc(2 * VECTOR_INIT_SIZE * sizeof(int));
	if (!deque->malloced_space)
		exit_on_err("init_deque error\n");
	ft_bzero(deque->malloced_space, 2 * VECTOR_INIT_SIZE);
	deque->elems			= &(deque->malloced_space[VECTOR_INIT_SIZE]);
	return ;
}

bool deque_add_front(t_deque *deque, int new_elem)
{
	bool		status;

	if (deque->capacity_front == 0)
	{
		status = deque_resize_front(deque, deque->capacity_total);
		if (status == FAILURE)
			return (status);
	}
	deque->elems -= 1;
	deque->elems[0] = new_elem;
	deque->nb_elems += 1;
	deque->capacity_front -= 1;
	deque->capacity_end += 1;
	if (new_elem > deque->elem_max)
		deque->elem_max = new_elem;
	if (new_elem < deque->elem_min)
		deque->elem_min = new_elem;
	status = SUCCESS;
	return (status);
}

bool deque_add_last(t_deque *deque, int new_elem)
{
	bool		status;

	if (deque->nb_elems == deque->capacity_end)
	{
		status = deque_resize_end(deque, deque->capacity_total * 2);
		if (status == FAILURE)
			return (status);
	}
	deque->elems[deque->nb_elems] = new_elem;
	deque->nb_elems += 1;
	if (new_elem > deque->elem_max)
		deque->elem_max = new_elem;
	if (new_elem < deque->elem_min)
		deque->elem_min = new_elem;
	status = SUCCESS;
	return (status);
}

void deque_free_list(t_deque *deque)
{
	free (deque->malloced_space);
	return ;
}

int	deque_get_elem_max(t_deque *deque)
{
	int			pos_in_stack;
	int			biggest_value;

	biggest_value = INT_MIN;
	pos_in_stack = 0;
	while (pos_in_stack < deque->nb_elems)
	{
		if (deque->elems[pos_in_stack] > biggest_value)
			biggest_value = deque->elems[pos_in_stack];
		pos_in_stack++;
	}
	return (biggest_value);
}

int	deque_get_elem_min(t_deque *deque)
{
	int			pos_in_stack;
	int			smallest_value;

	smallest_value = INT_MAX;
	pos_in_stack = 0;
	while (pos_in_stack < deque->nb_elems)
	{
		if (deque->elems[pos_in_stack] < smallest_value)
			smallest_value = deque->elems[pos_in_stack];
		pos_in_stack++;
	}
	return (smallest_value);
}

bool	deque_reinit_list(t_deque *deque)
{
	free(deque->malloced_space);
	deque->nb_elems			= 0;
	deque->elem_min			= deque->get_elem_min(deque);
	deque->elem_max			= deque->get_elem_max(deque);
	deque->capacity_end	= VECTOR_INIT_SIZE;
	deque->capacity_front	= VECTOR_INIT_SIZE;
	deque->capacity_total	= 2 * VECTOR_INIT_SIZE;
	deque->malloced_space	= malloc(2 * VECTOR_INIT_SIZE * sizeof(int));
	if (!deque->malloced_space)
		return (FAILURE);
	ft_bzero(deque->malloced_space, 2 * VECTOR_INIT_SIZE);
	deque->elems			= &(deque->malloced_space[VECTOR_INIT_SIZE]);
	return (SUCCESS);
}

//Need to add resize smaller when under a certain size
void	deque_remove_front(t_deque *deque)
{
	int	elem_to_be_removed;

	elem_to_be_removed = deque->elems[0];
	deque->elems[0] = 0;
	deque->elems += 1;
	deque->capacity_front += 1;
	deque->capacity_end -= 1;
	deque->nb_elems -= 1;
	if (elem_to_be_removed == deque->elem_min)
		deque->elem_min = deque->get_elem_min(deque);
	if (elem_to_be_removed == deque->elem_max)
		deque->elem_max = deque->get_elem_max(deque);
	return ;
}

//Need to add resize smaller when under a certain size
void	deque_remove_last(t_deque *deque)
{
	int	elem_to_be_removed;

	elem_to_be_removed = deque->elems[deque->nb_elems - 1];
	deque->elems[deque->nb_elems - 1] = 0;
	deque->nb_elems -= 1;
	if (elem_to_be_removed == deque->elem_min)
		deque->elem_min = deque->get_elem_min(deque);
	if (elem_to_be_removed == deque->elem_max)
		deque->elem_max = deque->get_elem_max(deque);
	return ;
}

bool deque_resize_front(t_deque *deque, int new_size)
{
	int		*temp;
	int		total_new_size;
	int		pos_in_deque;

	total_new_size = new_size + deque->capacity_end;
	temp = malloc(total_new_size * sizeof(int));
	if (!temp)
		return (FAILURE);
	temp += new_size;
	pos_in_deque = 0;
	while (pos_in_deque < deque->nb_elems)
	{
		temp[pos_in_deque] = deque->elems[pos_in_deque];
		pos_in_deque++;
	}
	free(deque->malloced_space);
	deque->malloced_space = temp - new_size;
	deque->elems = temp;
	deque->capacity_front = new_size;
	deque->capacity_total = total_new_size;
	return (SUCCESS);
}

bool deque_resize_end(t_deque *deque, int new_size)
{
	int		*temp;
	int		total_new_size;
	int		pos_in_deque;

	total_new_size = new_size + deque->capacity_front;
	temp = malloc(total_new_size * sizeof(int));
	if (!temp)
		return (FAILURE);
	temp += deque->capacity_front;
	pos_in_deque = 0;
	while (pos_in_deque < deque->nb_elems)
	{
		temp[pos_in_deque] = deque->elems[pos_in_deque];
		pos_in_deque++;
	}
	free(deque->malloced_space);
	deque->malloced_space = temp - deque->capacity_front;
	deque->elems = temp;
	deque->capacity_end = new_size;
	deque->capacity_total = total_new_size;
	return (SUCCESS);
}

void	deque_set_elem(t_deque *deque, int pos, int new_value)
{
	deque->elems[pos] = new_value;
	return ;
}
