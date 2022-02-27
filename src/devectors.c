#include "push_swap.h"

bool init_devec(t_vector *vec)
{
	//Add the atrocious list of helper functions(probs too much)
	vec->add_back = &vec_add_back;
	vec->add_front = &vec_add_front;
	vec->remove_back = &vec_remove_back;
	vec->remove_front = &vec_remove_front;
	vec->resize_back = &vec_resize_back;
	vec->resize_front = &vec_resize_front;
	vec->free_list = &vec_free_list;
	vec->set_elem = &vec_set_elem;
	vec->get_smallest_elem = &vec_get_smallest_elem;
	vec->get_biggest_elem = &vec_get_biggest_elem;

	//Malloc a block of memory designed to leave space on each side of the
	//vector_head, so that values can be added on both ends with the same
	//calculation cost, and there is still a single memory space.
	vec->nb_elems = 0;
	vec->smallest_elem = INT_MAX;
	vec->biggest_elem = INT_MIN;
	vec->capacity_after_head = VECTOR_INIT_SIZE;
	vec->capacity_before_head = VECTOR_INIT_SIZE;
	vec->capacity_total = 2 * VECTOR_INIT_SIZE;
	vec->malloced_space = malloc(2 * VECTOR_INIT_SIZE * sizeof(int));
	if (!vec->malloced_space)
		return (FAILURE);
	ft_bzero(vec->malloced_space, 2 * VECTOR_INIT_SIZE);
	vec->elems = &(vec->malloced_space[VECTOR_INIT_SIZE]);
	return (SUCCESS);
}

bool vec_add_back(t_vector *vec, int new_elem)
{
	bool		status;

	if (vec->nb_elems == vec->capacity_after_head)
	{
		status = vec_resize_back(vec, vec->capacity_total * 2);
		if (status == FAILURE)
			return (status);
	}
	vec->elems[vec->nb_elems] = new_elem;
	vec->nb_elems += 1;
	if (new_elem > vec->biggest_elem)
		vec->biggest_elem = new_elem;
	if (new_elem < vec->smallest_elem)
		vec->smallest_elem = 0;
	status = SUCCESS;
	return (status);
}

bool vec_add_front(t_vector *vec, int new_elem)
{
	bool		status;

	if (vec->capacity_before_head == 0)
	{
		status = vec_resize_front(vec, vec->capacity_total);
		if (status == FAILURE)
			return (status);
	}
	vec->elems -= 1;
	vec->elems[0] = new_elem;
	vec->nb_elems += 1;
	vec->capacity_before_head -= 1;
	if (new_elem > vec->biggest_elem)
		vec->biggest_elem = new_elem;
	if (new_elem < vec->smallest_elem)
		vec->smallest_elem = 0;
	status = SUCCESS;
	return (status);
}

//Need to add resize smaller when under a certain size
void	vec_remove_back(t_vector *vec)
{
	if (vec->elems[vec->nb_elems - 1] == vec->biggest_elem)
		vec->biggest_elem = vec->get_biggest_elem(vec);
	if (vec->elems[vec->nb_elems - 1] == vec->smallest_elem)
		vec->smallest_elem = vec->get_smallest_elem(vec);
	vec->elems[vec->nb_elems - 1] = 0;
	vec->nb_elems -= 1;
	return ;
}

//Need to add resize smaller when under a certain size
void	vec_remove_front(t_vector *vec)
{
	if (vec->elems[0] == vec->biggest_elem)
		vec->biggest_elem = vec->get_biggest_elem(vec);
	if (vec->elems[0] == vec->smallest_elem)
		vec->smallest_elem = vec->get_smallest_elem(vec);
	vec->elems[0] = 0;
	vec->elems += 1;
	vec->capacity_before_head += 1;
	vec->nb_elems -= 1;
	return ;
}

bool vec_resize_back(t_vector *vec, int new_size)
{
	int		*temp;
	int		total_new_size;
	int		pos_in_vector;
	bool	status;

	total_new_size = new_size + vec->capacity_before_head;
	//To switch to a bzero, or write a ft_calloc
	if (ft_assign_calloc((void **)&temp, total_new_size, sizeof(int)))
		status = FAILURE;
	else
	{
		temp += vec->capacity_before_head;
		pos_in_vector = 0;
		while (pos_in_vector < vec->nb_elems)
		{
			temp[pos_in_vector] = vec->elems[pos_in_vector];
			pos_in_vector++;
		}
		vec->elems = temp;
		free(vec->malloced_space);
		vec->malloced_space = temp - vec->capacity_before_head;
		vec->capacity_after_head = new_size;
		vec->capacity_total = total_new_size;
		status = SUCCESS;
	}
	return (status);
}

bool vec_resize_front(t_vector *vec, int new_size)
{
	int		*temp;
	int		total_new_size;
	int		pos_in_vector;
	bool	status;

	total_new_size = new_size + vec->capacity_after_head;
	//To switch to a bzero, or write a ft_calloc
	if (ft_assign_calloc((void **)&temp, total_new_size, sizeof(int)))
		status = FAILURE;
	else
	{
		temp += new_size;
		pos_in_vector = 0;
		while (pos_in_vector < vec->nb_elems)
		{
			temp[pos_in_vector] = vec->elems[pos_in_vector];
			pos_in_vector++;
		}
		vec->elems = temp;
		vec->malloced_space = temp - new_size;
		vec->capacity_before_head = new_size;
		vec->capacity_total = total_new_size;
		status = SUCCESS;
	}
	return (status);
}

void vec_free_list(t_vector *vec)
{
	free (vec->malloced_space);
	return ;
}

void	vec_set_elem(t_vector *vec, int pos, int new_value)
{
	vec->elems[pos] = new_value;
	return ;
}

int	vec_get_smallest_elem(t_vector *vec)
{
	int			pos_in_stack;
	int			smallest_value;
	int			pos_smallest_value;

	smallest_value = INT_MAX;
	pos_smallest_value = 0;
	pos_in_stack = 0;
	while (pos_in_stack < vec->nb_elems)
	{
		if (vec->elems[pos_in_stack] < smallest_value)
		{
			smallest_value = vec->elems[pos_in_stack];
			pos_smallest_value = pos_in_stack;
		}
		pos_in_stack++;
	}
	return (smallest_value);
}

int	vec_get_biggest_elem(t_vector *vec)
{
	int			pos_in_stack;
	int			biggest_value;
	int			pos_biggest_value;

	biggest_value = INT_MIN;
	pos_biggest_value = 0;
	pos_in_stack = 0;
	while (pos_in_stack < vec->nb_elems)
	{
		if (vec->elems[pos_in_stack] > biggest_value)
		{
			biggest_value = vec->elems[pos_in_stack];
			pos_biggest_value = pos_in_stack;
		}
		pos_in_stack++;
	}
	return (biggest_value);
}
