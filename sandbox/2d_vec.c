#include "push_swap.h"

typedef struct s_vec_2d_list
{
	t_vector	*vectors;
	int			capacity;
	int			nb_vecs;
}	t_vec_2d_list;

typedef struct s_vec_2d t_vec_2d;
typedef	struct s_vec_2d
{
	t_vec_2d_list	list;
	bool			(*add)(t_vec_2d *, t_vector);
	void			(*remove)(t_vec_2d *);
	bool			(*resize)(t_vec_2d *, int);
	bool			(*add_vec_2d)(t_vec_2d *, t_vec_2d *);
	bool			(*free_list)(t_vec_2d *);
}	t_vec_2d;

bool	init_vec_2d(t_vec_2d *vec_2d);
bool	vec_2d_add(t_vec_2d *vec_2d, t_vector new_ve);
void	vec_2d_remove(t_vec_2d *vec_2d);
bool	vec_2d_resize(t_vec_2d *vec_2d, int new_size);
bool	vec_2d_add_vec_2d(t_vec_2d *vec_2d, t_vec_2d *);
bool	vec_2d_free_list(t_vec_2d *vec_2d);

bool	init_vec_2d(t_vec_2d *vec_2d)
{
	vec_2d->add = &vec_2d_add;
	vec_2d->remove = &vec_2d_add;
	vec_2d->resize = &vec_2d_remove;
	vec_2d->add_vec_2d = &vec_2d_remove;
	vec_2d->free_list = &vec_2d_resize;

	vec_2d.nb_vecs = 0;
	vec_2d.capacity = VECTOR_INIT_SIZE;
	vec_2d.vectors = malloc(VECTOR_INIT_SIZE * sizeof(t_vector));
	if (!vec_2d.vectors)
		return (FAILURE);
	return (SUCCESS);
}

bool			vec_2d_add(t_vec_2d *vec_2d, t_vector new_vec)
{
	bool	status;

	if (vec_2d.nb_vecs == vec_2d.capacity)
	{
		status = vec_2d_resize(vec_2d, 2 * vec_2d.capacity);
		if (status == FAILURE)
			return (status);
	}
	vec_2d.vectors[vec_wd.nb_vecs] = new_vec
	vec_2d.nb_vecs += 1;
	vec_2d.capacity -= 1;
	status = SUCCESS;
	return (status);
}

void			vec_2d_remove(t_vec_2d *vec_2d)
{
	t_vector *vector_to_remove;

	vector_to_remove = &vec_2d.vectors[vec_2d.nb_vecs - 1];
	vector_to_remove->free_list(vector_to_remove);
	vec_2d.vectors[vec_2d.nb_vecs - 1] = NULL;
	vec_2d.nb_vecs -= 1;
	vec_2d.capacity += 1;
	return ;
}

bool			vec_2d_resize(t_vec_2d *vec_2d, int new_size)
{
	t_vector	*temp;
	int			pos_in_vector;
	bool		status;

	temp = malloc(new_size * sizeof(vector));
	if (!temp)
		status = FAILURE;
	else
	{
		pos_in_vector = 0;
		while (pos_in_vector < 2d_vec>list.nb_vecs)
		{
			temp[pos_in_vector] = vector.elems[pos_in_vector];
			pos_in_vector++;
		}
		vector.vecs = temp;
		free(vector.malloced_space);
		vector.malloced_space = temp - vector.capacity_before_head;
		vector.capacity_after_head = new_size;
		vector.capacity_total = new_size + vector.capacity_before_head;
		status = SUCCESS;
	}
	return (status);
}

bool			vec_2d_add_vec_2d(t_vec_2d *vec_2d, t_vec_2d *)
{

}

bool			vec_2d_free_list(t_vec_2d *vec_2d)
{

}
