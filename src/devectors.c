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
	vector->get_elems = &vec_get_elems;
	vector->get_size = &vec_get_size;
	vector->set_elem = &vec_set_elem;
	vector->get_elem = &vec_get_elem;

	//Malloc a block of memory designed to leave space on each side of the
	//vector_head, so that values can be added on both ends with the same
	//calculation cost, and there is still a single memory space.
	vector->list.nb_elems = 0;
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
	status = SUCCESS;
	return (status);
}

//Need to add resize smaller when under a certain size
void	vec_remove_back(t_vector *vector)
{
	vector->list.elems[vector->list.nb_elems - 1] = 0;
	vector->list.nb_elems -= 1;
	return ;
}

//Need to add resize smaller when under a certain size
void	vec_remove_front(t_vector *vector)
{
	vector->list.elems[0] = 0;
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
	if (DEBUG)
		printf(RED"ENTERED RESIZE_END() WITH SIZE = %d\n", total_new_size);
	//To switch to a bzero, or write a ft_calloc
	if (ft_assign_calloc((void **)&temp, total_new_size, sizeof(int)))
		status = FAILURE;
	else
	{
		if (DEBUG)
			printf("SURVIVED MALLOC\n"RESET_COL);
		temp += vector->list.capacity_before_head;
		pos_in_vector = 0;
		while (pos_in_vector < vector->list.nb_elems)
		{
			temp[pos_in_vector] = vector->list.elems[pos_in_vector];
			pos_in_vector++;
		}
		vector->list.elems = temp;
		free(vector->list.malloced_space);
		if (DEBUG)
			printf(RED"SURVIVED FREE()\n"RESET_COL);
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
	if (DEBUG)
		printf(MAGENTA"ENTERED RESIZE_BEGIN() WITH SIZE = %d\n", total_new_size);
	//To switch to a bzero, or write a ft_calloc
	if (ft_assign_calloc((void **)&temp, total_new_size, sizeof(int)))
		status = FAILURE;
	else
	{
		if (DEBUG)
			printf("SURVIVED MALLOC\n"RESET_COL);
		temp += new_size;
		pos_in_vector = 0;
		while (pos_in_vector < vector->list.nb_elems)
		{
			temp[pos_in_vector] = vector->list.elems[pos_in_vector];
			pos_in_vector++;
		}
		vector->list.elems = temp;
		if (DEBUG)
			free(vector->list.malloced_space);
		printf(MAGENTA"SURVIVED FREE()\n"RESET_COL);
		vector->list.malloced_space = temp - new_size;
		vector->list.capacity_before_head = new_size;
		vector->list.capacity_total = new_size + vector->list.capacity_after_head;
		status = SUCCESS;
	}
	return (status);
}

int *vec_get_elems(t_vector *vector)
{
	return ((int *const) vector->list.elems);
}

int	vec_get_size(t_vector *vector)
{
	return (vector->list.nb_elems);
}

bool vec_free_list(t_vector *vector)
{
	free (vector->list.malloced_space);
	return (FAILURE);
}

int		vec_get_elem(t_vector *vector, int pos)
{
	return(vector->list.elems[pos]);
}

void	vec_set_elem(t_vector *vector, int pos, int new_value)
{
	vector->list.elems[pos] = new_value;
	return ;
}
