#include "push_swap.h"

bool init_deque(t_deque *deque)
{
	//Add the atrocious list of helper functions(probs too much)
	deque->add_last = &deque_add_last;
	deque->add_front = &deque_add_front;
	deque->remove_last = &deque_remove_last;
	deque->remove_front = &deque_remove_front;
	deque->resize_last = &deque_resize_last;
	deque->resize_front = &deque_resize_front;
	deque->free_list = &deque_free_list;
	deque->set_elem = &deque_set_elem;
	deque->get_min_elem = &deque_get_min_elem;
	deque->get_max_elem = &deque_get_max_elem;

	//Malloc a block of memory designed to leave space on each side of the
	//deque_head, so that values can be added on both ends with the same
	//calculation cost, and there is still a single memory space.
	deque->nb_elems = 0;
	deque->min_elem = deque->get_min_elem(deque);
	deque->max_elem = deque->get_max_elem(deque);
	deque->capacity_after_head = VECTOR_INIT_SIZE;
	deque->capacity_before_head = VECTOR_INIT_SIZE;
	deque->capacity_total = 2 * VECTOR_INIT_SIZE;
	deque->malloced_space = malloc(2 * VECTOR_INIT_SIZE * sizeof(int));
	if (!deque->malloced_space)
		return (FAILURE);
	ft_bzero(deque->malloced_space, 2 * VECTOR_INIT_SIZE);
	deque->elems = &(deque->malloced_space[VECTOR_INIT_SIZE]);
	return (SUCCESS);
}

bool deque_add_last(t_deque *deque, int new_elem)
{
	bool		status;

	if (deque->nb_elems == deque->capacity_after_head)
	{
		status = deque_resize_last(deque, deque->capacity_total * 2);
		if (status == FAILURE)
			return (status);
	}
	deque->elems[deque->nb_elems] = new_elem;
	deque->nb_elems += 1;
	if (new_elem > deque->max_elem)
		deque->max_elem = new_elem;
	if (new_elem < deque->min_elem)
		deque->min_elem = new_elem;
	status = SUCCESS;
	return (status);
}

bool deque_add_front(t_deque *deque, int new_elem)
{
	bool		status;

	if (deque->capacity_before_head == 0)
	{
		status = deque_resize_front(deque, deque->capacity_total);
		if (status == FAILURE)
			return (status);
	}
	deque->elems -= 1;
	deque->elems[0] = new_elem;
	deque->nb_elems += 1;
	deque->capacity_before_head -= 1;
	if (new_elem > deque->max_elem)
		deque->max_elem = new_elem;
	if (new_elem < deque->min_elem)
		deque->min_elem = new_elem;
	status = SUCCESS;
	return (status);
}

//Need to add resize smaller when under a certain size
void	deque_remove_last(t_deque *deque)
{
	int	elem_to_be_removed;

	elem_to_be_removed = deque->elems[deque->nb_elems - 1];
	deque->elems[deque->nb_elems - 1] = 0;
	deque->nb_elems -= 1;
	if (elem_to_be_removed == deque->min_elem)
		deque->min_elem = deque->get_min_elem(deque);
	if (elem_to_be_removed == deque->max_elem)
		deque->max_elem = deque->get_max_elem(deque);
	return ;
}

//Need to add resize smaller when under a certain size
void	deque_remove_front(t_deque *deque)
{
	int	elem_to_be_removed;

	elem_to_be_removed = deque->elems[0];
	deque->elems[0] = 0;
	deque->elems += 1;
	deque->capacity_before_head += 1;
	deque->nb_elems -= 1;
	if (elem_to_be_removed == deque->min_elem)
		deque->min_elem = deque->get_min_elem(deque);
	if (elem_to_be_removed == deque->max_elem)
		deque->max_elem = deque->get_max_elem(deque);
	return ;
}

bool deque_resize_last(t_deque *deque, int new_size)
{
	int		*temp;
	int		total_new_size;
	int		pos_in_deque;

	total_new_size = new_size + deque->capacity_before_head;
	if (ft_assign_calloc((void **)&temp, total_new_size, sizeof(int)))
		return (FAILURE);
	temp += deque->capacity_before_head;
	pos_in_deque = 0;
	while (pos_in_deque < deque->nb_elems)
	{
		temp[pos_in_deque] = deque->elems[pos_in_deque];
		pos_in_deque++;
	}
	free(deque->malloced_space);
	deque->malloced_space = temp - deque->capacity_before_head;
	deque->elems = temp;
	deque->capacity_after_head = new_size;
	deque->capacity_total = total_new_size;
	return (SUCCESS);
}

bool deque_resize_front(t_deque *deque, int new_size)
{
	int		*temp;
	int		total_new_size;
	int		pos_in_deque;

	total_new_size = new_size + deque->capacity_after_head;
	if (ft_assign_calloc((void **)&temp, total_new_size, sizeof(int)))
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
	deque->capacity_before_head = new_size;
	deque->capacity_total = total_new_size;
	return (SUCCESS);
}

void deque_free_list(t_deque *deque)
{
	free (deque->malloced_space);
	return ;
}

void	deque_set_elem(t_deque *deque, int pos, int new_value)
{
	if (pos < deque->capacity_before_head || pos > deque->capacity_after_head)
		return ;
	deque->elems[pos] = new_value;
	return ;
}

int	deque_get_min_elem(t_deque *deque)
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

int	deque_get_max_elem(t_deque *deque)
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
