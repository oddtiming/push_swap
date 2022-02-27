#include "push_swap.h"

bool init_devec(t_vector *vector)
{
	//Add the atrocious list of helper functions(probs too much)
	vector->add_back = &vec_add_back;
	vector->add_front = &vec_add_front;
	vector->remove_back = &vec_remove_back;
	vector->remove_front = &vec_remove_front;
	vector->resize_back = &vec_resize_back;
	vector->resize_front = &vec_resize_front;
	vector->free_list = &vec_free_list;
	vector->set_elem = &vec_set_elem;
	vector->get_smallest_elem = &vec_get_smallest_elem;
	vector->get_biggest_elem = &vec_get_biggest_elem;

	//Malloc a block of memory designed to leave space on each side of the
	//vector_head, so that values can be added on both ends with the same
	//calculation cost, and there is still a single memory space.
	vector->list.nb_elems = 0;
	vector->list.smallest_elem = INT_MAX;
	vector->list.biggest_elem = INT_MIN;
	vector->list.capacity_after_head = VECTOR_INIT_SIZE;
	vector->list.capacity_before_head = VECTOR_INIT_SIZE;
	vector->list.capacity_total = 2 * VECTOR_INIT_SIZE;
	vector->list.malloced_space = malloc(2 * VECTOR_INIT_SIZE * sizeof(int));
	if (!vector->list.malloced_space)
		return (FAILURE);
	ft_bzero(vector->list.malloced_space, 2 * VECTOR_INIT_SIZE);
	vector->list.elems = &(vector->list.malloced_space[VECTOR_INIT_SIZE]);
	return (SUCCESS);
}

bool vec_add_back(t_vector *vector, int new_elem)
{
	bool		status;

	if (vector->list.nb_elems == vector->list.capacity_after_head)
	{
		status = vec_resize_back(vector, vector->list.capacity_total * 2);
		if (status == FAILURE)
			return (status);
	}
	vector->list.elems[vector->list.nb_elems] = new_elem;
	vector->list.nb_elems += 1;
	if (new_elem > vector->list.biggest_elem)
		vector->list.biggest_elem = new_elem;
	if (new_elem < vector->list.smallest_elem)
		vector->list.smallest_elem = 0;
	status = SUCCESS;
	return (status);
}

bool vec_add_front(t_vector *vector, int new_elem)
{
	bool		status;

	if (vector->list.capacity_before_head == 0)
	{
		status = vec_resize_front(vector, vector->list.capacity_total);
		if (status == FAILURE)
			return (status);
	}
	vector->list.elems -= 1;
	vector->list.elems[0] = new_elem;
	vector->list.nb_elems += 1;
	vector->list.capacity_before_head -= 1;
	if (new_elem > vector->list.biggest_elem)
		vector->list.biggest_elem = new_elem;
	if (new_elem < vector->list.smallest_elem)
		vector->list.smallest_elem = 0;
	status = SUCCESS;
	return (status);
}

//Need to add resize smaller when under a certain size
void	vec_remove_back(t_vector *vector)
{
	int *elem_to_be_removed;

	elem_to_be_removed = &vector->list.elems[vector->list.nb_elems - 1];
	if (*elem_to_be_removed > vector->list.biggest_elem)
		vector->list.biggest_elem = vector->get_biggest_elem(vector);
	if (*elem_to_be_removed < vector->list.smallest_elem)
		vector->list.smallest_elem = vector->get_smallest_elem(vector);
	*elem_to_be_removed = 0;
	vector->list.nb_elems -= 1;
	return ;
}

//Need to add resize smaller when under a certain size
void	vec_remove_front(t_vector *vector)
{
	int *elem_to_be_removed;

	elem_to_be_removed = &vector->list.elems[0];
	if (*elem_to_be_removed > vector->list.biggest_elem)
		vector->list.biggest_elem = vector->get_biggest_elem(vector);
	if (*elem_to_be_removed < vector->list.smallest_elem)
		vector->list.smallest_elem = vector->get_smallest_elem(vector);
	*elem_to_be_removed = 0;
	vector->list.elems += 1;
	vector->list.capacity_before_head += 1;
	vector->list.nb_elems -= 1;
	return ;
}

bool vec_resize_back(t_vector *vector, int new_size)
{
	int		*temp;
	int		total_new_size;
	int		pos_in_vector;
	bool	status;

	total_new_size = new_size + vector->list.capacity_before_head;
	//To switch to a bzero, or write a ft_calloc
	if (ft_assign_calloc((void **)&temp, total_new_size, sizeof(int)))
		status = FAILURE;
	else
	{
		temp += vector->list.capacity_before_head;
		pos_in_vector = 0;
		while (pos_in_vector < vector->list.nb_elems)
		{
			temp[pos_in_vector] = vector->list.elems[pos_in_vector];
			pos_in_vector++;
		}
		vector->list.elems = temp;
		free(vector->list.malloced_space);
		vector->list.malloced_space = temp - vector->list.capacity_before_head;
		vector->list.capacity_after_head = new_size;
		vector->list.capacity_total = new_size + vector->list.capacity_before_head;
		status = SUCCESS;
	}
	return (status);
}

bool vec_resize_front(t_vector *vector, int new_size)
{
	int		*temp;
	int		total_new_size;
	int		pos_in_vector;
	bool	status;

	total_new_size = new_size + vector->list.capacity_after_head;
	//To switch to a bzero, or write a ft_calloc
	if (ft_assign_calloc((void **)&temp, total_new_size, sizeof(int)))
		status = FAILURE;
	else
	{
		temp += new_size;
		pos_in_vector = 0;
		while (pos_in_vector < vector->list.nb_elems)
		{
			temp[pos_in_vector] = vector->list.elems[pos_in_vector];
			pos_in_vector++;
		}
		vector->list.elems = temp;
		printf(MAGENTA"SURVIVED FREE()\n"RESET_COL);
		vector->list.malloced_space = temp - new_size;
		vector->list.capacity_before_head = new_size;
		vector->list.capacity_total = new_size + vector->list.capacity_after_head;
		status = SUCCESS;
	}
	return (status);
}

void vec_free_list(t_vector *vector)
{
	free (vector->list.malloced_space);
	return ;
}

void	vec_set_elem(t_vector *vector, int pos, int new_value)
{
	vector->list.elems[pos] = new_value;
	return ;
}

int	vec_get_smallest_elem(t_vector *vector)
{
	int			pos_in_stack;
	int			smallest_value;
	int			pos_smallest_value;

	smallest_value = INT_MAX;
	pos_smallest_value = 0;
	pos_in_stack = 0;
	while (pos_in_stack < vector->list.nb_elems)
	{
		if (vector->list.elems[pos_in_stack] < smallest_value)
		{
			smallest_value = vector->list.elems[pos_in_stack];
			pos_smallest_value = pos_in_stack;
		}
		pos_in_stack++;
	}
	return (smallest_value);
}

int	vec_get_biggest_elem(t_vector *vector)
{
	int			pos_in_stack;
	int			biggest_value;
	int			pos_biggest_value;

	biggest_value = INT_MIN;
	pos_biggest_value = 0;
	pos_in_stack = 0;
	while (pos_in_stack < vector->list.nb_elems)
	{
		if (vector->list.elems[pos_in_stack] > biggest_value)
		{
			biggest_value = vector->list.elems[pos_in_stack];
			pos_biggest_value = pos_in_stack;
		}
		pos_in_stack++;
	}
	return (biggest_value);
}
