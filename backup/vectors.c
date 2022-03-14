#include "push_swap.h"

bool vector_init(t_vector *vector)
{
	vector->ptr_vec_add = vec_add;
	vector->ptr_vec_remove = vec_remove;
	vector->ptr_vec_resize = vec_resize;
	vector->ptr_vec_free_list = vec_free_list;

	vector.nb_elems = 0;
	vector.capacity = VECTOR_INIT_SIZE;
	vector.elems = malloc(VECTOR_INIT_SIZE * sizeof(int *));
	if (!vector.elems)
		return (FAILURE);
	return (SUCCESS);
}

bool vec_add(t_vector *vector, int new_elem)
{
	t_vec_list	*list;
	bool		status;

	list = &vector;
	if (list->nb_elems == list->capacity)
	{
		status = vec_resize(vector, list->capacity + list->capacity);
		if (status == FAILURE)
			return (status);
	}
	list->elems[list->nb_elems] = new_elem;
	list->nb_elems += 1;
	status = SUCCESS;
	return (status);
}

//Need to add resize smaller when under a certain size
void	vec_remove(t_vector *vector)
{
	t_vec_list	*list;

	list = &vector;
	list->elems[list->nb_elems - 1] = 0;
	list->nb_elems -= 1;
	return ;
}

bool vec_resize(t_vector *vector, int new_size)
{
	int		*temp;
	int		pos_in_vector;
	bool	status;

	if (new_size < vector.capacity)
		return (FAILURE);
	if (DEBUG)
		printf(RED"ENTERED RESIZE_END() WITH SIZE = %d\n", new_size);
	//To switch to a bzero, or write a ft_calloc
	temp = malloc(new_size * sizeof(int));
	if (DEBUG)
		printf("SURVIVED MALLOC\n"RESET_COL);
	if (!temp)
		status = FAILURE;
	else
	{
		ft_bzero(temp, new_size);
		pos_in_vector = 0;
		while (pos_in_vector < vector.nb_elems)
		{
			temp[pos_in_vector] = vector.elems[pos_in_vector];
			pos_in_vector++;
		}
		free (vector.elems);
		vector.elems = temp;
		if (DEBUG)
			printf(RED"SURVIVED FREE()\n"RESET_COL);
		vector.capacity = new_size;
		status = SUCCESS;
	}
	return (status);
}

bool vec_free_list(t_vector *vector)
{
	free (vector.elems);
	return (FAILURE);
}
