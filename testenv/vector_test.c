//Learned structure from https://aticleworld.com/implement-vector-in-c/
//Decided to fuck it up of my own volition, though
#include "../include/push_swap.h"

# define VECTOR_INIT_SIZE 16
# define SUCCESS true
# define FAILURE false

typedef struct s_vec_list
{
	int	*elems;
	int	**malloced_space;
	int	nb_elems;
	int	capacity_total;
	int	capacity_after_head;
	int	capacity_before_head;
}	t_vec_list;

typedef struct s_vector t_vector;
typedef struct s_vector
{
	t_vec_list	list;
	bool		(*ptr_add_end)(t_vector *, int );
	bool		(*ptr_add_begin)(t_vector *, int );
	void		(*ptr_remove_end)(t_vector *);
	void		(*ptr_remove_begin)(t_vector *);
	bool		(*ptr_resize_end)(t_vector *, int);
	bool		(*ptr_resize_begin)(t_vector *, int);
	bool		(*ptr_free_list)(t_vector *);
}	t_vector;

bool 	vector_init(t_vector *vector);
bool 	vec_add(t_vector *vector, int new_elem);
bool 	add_begin(t_vector *vector, int new_elem);
void	vec_remove(t_vector *vector);
void	remove_begin(t_vector *vector);
bool 	vec_resize(t_vector *vector, int new_size);
bool 	resize_begin(t_vector *vector, int new_size);
bool 	vec_free_list(t_vector *vector);


bool vector_init(t_vector *vector)
{
	vector->ptr_add_end = vec_add;
	vector->ptr_add_begin = add_begin;
	vector->ptr_remove_end = vec_remove;
	vector->ptr_remove_begin = remove_begin;
	vector->ptr_resize_end = vec_resize;
	vector->ptr_resize_begin = resize_begin;
	vector->ptr_free_list = vec_free_list;

	vector->list.nb_elems = 0;
	vector->list.capacity_after_head = VECTOR_INIT_SIZE;
	vector->list.capacity_before_head = VECTOR_INIT_SIZE;
	vector->list.capacity_total = 2 * VECTOR_INIT_SIZE;
	vector->list.malloced_space = malloc(2 * VECTOR_INIT_SIZE * sizeof(int));
	if (!vector->list.malloced_space)
		return (FAILURE);
	vector->list.elems = &(vector->list.malloced_space[VECTOR_INIT_SIZE]);
	return (SUCCESS);
}

bool vec_add(t_vector *vector, int new_elem)
{
	t_vec_list	*list;
	bool		status;

	list = &vector->list;
	if (list->nb_elems == list->capacity_after_head)
	{
		status = vec_resize(vector, list->capacity_total * 2);
		if (status == FAILURE)
			return (status);
	}
	list->elems[list->nb_elems] = new_elem;
	list->nb_elems += 1;
	status = SUCCESS;
	return (status);
}

bool add_begin(t_vector *vector, int new_elem)
{
	t_vec_list	*list;
	bool		status;

	list = &vector->list;
	if (list->capacity_before_head == 0)
	{
		status = resize_begin(vector, list->capacity_total);
		if (status == FAILURE)
			return (status);
	}
	list->elems -= 1;
	list->elems[0] = new_elem;
	list->nb_elems += 1;
	list->capacity_before_head -= 1;
	status = SUCCESS;
	return (status);
}

//Need to add resize smaller when under a certain size
void	vec_remove(t_vector *vector)
{
	t_vec_list	*list;

	list = &vector->list;
	list->elems[list->nb_elems - 1] = 0;
	list->nb_elems -= 1;
	return ;
}

//Need to add resize smaller when under a certain size
void	remove_begin(t_vector *vector)
{
	t_vec_list	*list;

	list = &vector->list;
	list->elems[0] = NULL;
	list->elems += 1;
	list->capacity_before_head += 1;
	list->nb_elems -= 1;
	return ;
}

bool vec_resize(t_vector *vector, int new_size)
{
	int		*temp;
	int		total_new_size;
	int		pos_in_vector;
	bool	status;

	total_new_size = new_size + vector->list.capacity_before_head;
	if (DEBUG)
		printf(RED"ENTERED RESIZE_END() WITH SIZE = %d\n", total_new_size);
	//To switch to a bzero, or write a ft_calloc
	if (DEBUG)
		temp = calloc(total_new_size, sizeof(int));
	printf("SURVIVED MALLOC\n"RESET_COL);
	if (!temp)
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
		if (DEBUG)
			printf(RED"SURVIVED FREE()\n"RESET_COL);
		vector->list.malloced_space = temp - vector->list.capacity_before_head;
		vector->list.capacity_total = new_size;
		status = SUCCESS;
	}
	return (status);
}

bool resize_begin(t_vector *vector, int new_size)
{
	int		*temp;
	int		total_new_size;
	int		pos_in_vector;
	bool	status;

if (DEBUG)
		total_new_size = new_size + vector->list.capacity_total;
	printf(MAGENTA"ENTERED RESIZE_BEGIN() WITH SIZE = %d\n", total_new_size);
	//To switch to a bzero, or write a ft_calloc
	if (DEBUG)
		temp = calloc(total_new_size, sizeof(int));
	printf("SURVIVED MALLOC\n"RESET_COL);
	if (!temp)
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
		if (DEBUG)
			free(vector->list.malloced_space);
		printf(MAGENTA"SURVIVED FREE()\n"RESET_COL);
		vector->list.malloced_space = temp - new_size;
		vector->list.capacity_before_head = new_size;
		status = SUCCESS;
	}
	return (FAILURE);
}

bool vec_free_list(t_vector *vector)
{
	free (vector->list.malloced_space);
	return (FAILURE);
}

int	main(void)
{
	t_vector	vec;
	int			elem1 = 30;
	int			elem2 = 4;
	int			elem_list1[4] = {1, 3, 5, -2};
	int			long_list_size = 5500;
	int			*long_list1;
	int			*long_list2;

	vector_init(&vec);

	printf(YELLOW"-----After vector_init-----\n");
	printf("vec.list.nb_elems = %d\n", vec.list.nb_elems);
	printf("vec.list.capacity_before_head = %d\n", vec.list.capacity_before_head);
	printf("vec.list.capacity_end = %d\n", vec.list.capacity_total);
	printf("vec.list.malloced_space = %p\n", vec.list.malloced_space);
	printf("vec.list.elems = %p\n"RESET_COL, vec.list.elems);


	vec.ptr_add_end(&vec, &elem1);
	vec.ptr_add_end(&vec, &elem2);
	vec.ptr_add_begin(&vec, &elem_list1[0]);

	printf(GREEN"\n-----After adding some shit-----\n");
	printf("vec.list.nb_elems (should be 3) = %d\n", vec.list.nb_elems);
	printf("vec.list.capacity_before_head (should be 15) = %d\n", vec.list.capacity_before_head);
	printf("vec.list.capacity_end (should be 14) = %d\n", vec.list.capacity_total);
	printf("vec.list.malloced_space (should be the same) = %p\n", vec.list.malloced_space);
	printf("vec.list.elems (should be -= 1) = %p\n"RESET_COL, vec.list.elems);

	printf(MAGENTA"\n-----Accessing elements-----\n");
	printf("vec.list.elems[0][0] (should be 1) = %d\n", vec.list.elems[0][0]);
	printf("vec.list.elems[0][1] (should be 3) = %d\n", vec.list.elems[0][1]);
	printf("vec.list.elems[0][2] (should be 5) = %d\n", vec.list.elems[0][2]);
	printf("vec.list.elems[0][3] (should be -2) = %d\n", vec.list.elems[0][3]);
	printf("*vec.list.elems[1] (should be 30) = %d\n", *vec.list.elems[1]);
	printf("*vec.list.elems[2] (should be 4) = %d\n"RESET_COL, *vec.list.elems[2]);


	if (!(long_list1 = malloc(long_list_size * sizeof(int))))
	{
		printf("Oopsie fucky in the malloc department\n");
		exit(EXIT_FAILURE);
	}
	if (!(long_list2 = malloc(long_list_size * sizeof(int))))
	{
		printf("Oopsie fucky in the malloc department\n");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < long_list_size; i++)
	{
		long_list1[i] = i;
		vec.ptr_add_end(&vec, &long_list1[i]);
	}
	for (int i = 0; i < long_list_size; i++)
	{
		long_list2[i] = i;
		vec.ptr_add_begin(&vec, &long_list2[i]);
	}

	printf(GREEN"\n-----After adding two long lists of elems-----\n");
	printf("vec.list.nb_elems = %d\n", vec.list.nb_elems);
	printf("vec.list.capacity_before_head = %d\n", vec.list.capacity_before_head);
	printf("vec.list.capacity_end= %d\n", vec.list.capacity_total);
	printf("vec.list.malloced_space = %p\n", vec.list.malloced_space);
	printf("vec.list.elems= %p\n", vec.list.elems);
	printf("Diff between the two addresses = %d\n"RESET_COL, (int) ((vec.list.elems - vec.list.malloced_space)));



	printf(RED"Attempting vec.free_list()\n"RESET_COL);
	vec.ptr_free_list(&vec);
	free(long_list1);
	free(long_list2);
	return (EXIT_SUCCESS);
}
