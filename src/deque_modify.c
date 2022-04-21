#include "deques.h"

bool	deque_add_front(t_deque *deque, int new_elem)
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
	deque->size += 1;
	deque->capacity_front -= 1;
	deque->capacity_end += 1;
	if (new_elem > deque->max_elem)
		deque->max_elem = new_elem;
	if (new_elem < deque->min_elem)
		deque->min_elem = new_elem;
	status = SUCCESS;
	return (status);
}

bool deque_add_last(t_deque *deque, int new_elem)
{
	bool		status;

	if (deque->size == deque->capacity_end)
	{
		status = deque_resize_end(deque, deque->capacity_total * 2);
		if (status == FAILURE)
			return (status);
	}
	deque->elems[deque->size] = new_elem;
	deque->size += 1;
	if (new_elem > deque->max_elem)
		deque->max_elem = new_elem;
	if (new_elem < deque->min_elem)
		deque->min_elem = new_elem;
	status = SUCCESS;
	return (status);
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
	deque->size -= 1;
	if (elem_to_be_removed == deque->min_elem)
		deque->min_elem = deque->get_elem_min(deque);
	if (elem_to_be_removed == deque->max_elem)
		deque->max_elem = deque->get_elem_max(deque);
	return ;
}

//Need to add resize smaller when under a certain size
void	deque_remove_last(t_deque *deque)
{
	int	elem_to_be_removed;

	elem_to_be_removed = deque->elems[deque->size - 1];
	deque->elems[deque->size - 1] = 0;
	deque->size -= 1;
	if (elem_to_be_removed == deque->min_elem)
		deque->min_elem = deque->get_elem_min(deque);
	if (elem_to_be_removed == deque->max_elem)
		deque->max_elem = deque->get_elem_max(deque);
	return ;
}

void	deque_set_elem(t_deque *deque, int pos, int new_value)
{
	deque->elems[pos] = new_value;
	return ;
}
