#ifndef VECTORS_H
# define VECTORS_H

# include "push_swap.h"

# define VECTOR_INIT_SIZE 16
# define SUCCESS true
# define FAILURE false

typedef struct s_vec_list
{
	int *elems;
	int	nb_elems;
	int	capacity;
}	t_vec_list;

typedef struct s_vector t_vector;
typedef struct s_vector
{
	t_vec_list	list;
	bool		(*ptr_vec_add)(t_vector *, int);
	void		(*ptr_vec_remove)(t_vector *);
	bool		(*ptr_vec_resize)(t_vector *, int);
	bool		(*ptr_vec_free_list)(t_vector *);
}	t_vector;

bool 	vector_init(t_vector *vector);
bool 	vec_add(t_vector *vector, int new_elem);
void	vec_remove(t_vector *vector);
bool 	vec_resize(t_vector *vector, int new_size);
bool 	vec_free_list(t_vector *vector);

#endif