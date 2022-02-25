#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

//Includes; 
//stdlib.h	: malloc(), free(), exit()
//unistd.h	: read(), write()
//stdbool.h	: clarity for certain return values
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
//TO REMOVE
# include <stdio.h>
//END OF REMOVE

//libft for ft_putstr_fd(), ft_strlen(), ft_split()
# include "../libft/libft.h"

//DEFINES
# define _ARGC_MIN 2
# define VALID_INPUTS 1
# define MAX_MOVES_FOR_5 9

# define VECTOR_INIT_SIZE 16
# define SUCCESS 0
# define FAILURE 1

//TO REMOVE
# ifndef DEBUG
#  define DEBUG 0
# endif
# define YELLOW "\033[0;33m"
# define MAGENTA "\033[0;35m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define RESET_COL "\033[0m"
//END OF REMOVE

//TYPEDEFS
typedef struct s_vec_list
{
	int	*elems;
	int	*malloced_space;
	int	nb_elems;
	int	capacity_total;
	int	capacity_after_head;
	int	capacity_before_head;
}	t_vec_list;

typedef struct s_vector t_vector;
typedef struct s_vector
{
	t_vec_list	list;
	bool		(*add_back)(t_vector *, int);
	bool		(*add_front)(t_vector *, int);
	void		(*remove_back)(t_vector *);
	void		(*remove_front)(t_vector *);
	bool		(*resize_back)(t_vector *, int);
	bool		(*resize_front)(t_vector *, int);
	bool		(*free_list)(t_vector *);
	int			*(*get_elems)(t_vector *);
	int			(*get_size)(t_vector *);
	void		(*set_elem)(t_vector *, int, int);
	int			(*get_elem)(t_vector *, int);
}	t_vector;

typedef struct s_main_cont
{
	t_vector	a;
	t_vector	b;
	t_vector	*moves;
	int			size_total;
}	t_main_cont;

typedef enum e_moves
{
	RA = 1,
	RB = 2,
	RR = 3,
	RRA = 4,
	RRB = 5,
	RRR = 6,
	SA = 7,
	SB = 8,
	SS = 9,
	PA = 10,
	PB = 11
}	t_moves;

//Functions
//PARSING
void	parse(int argc, char *argv[], t_main_cont *cont);
void	assign_inputs(t_main_cont *cont, char **args, int size);
int		*normalize_stack_values(t_vector *stack);


//MOVES
void	rotate(int **stack, int size);
void	make_rab(int **stack, int size, int move);
void	rev_rotate(int **stack, int size);
void	make_rrab(int **stack, int size, int move);
void	swap(int *stack, int size);
void	make_sab(int *stack, int size, int move);
void	push(t_main_cont *cont, int move);
void	make_push(t_main_cont *cont, int move);

//SORTING
void	sort(t_main_cont *cont);
void	sort_3(t_main_cont *cont);
int		get_smallest_pos(int *stack, int size);
int		get_smallest_val(int *stack, int size);
int		get_biggest_val(int *stack, int size);
int		nb_sorted_at_pos(int *stack, int size, int pos);

//  SORT_5
void	sort_5(t_main_cont *cont);
void	rotate_a_to_pos0(t_main_cont *cont, int pos);
void	rotate_a_to_pos0_dry_run(t_main_cont *cont, int pos);
void	insert_b(t_main_cont *cont);
bool	try_rotate_and_swap(t_main_cont *cont);
bool	try_ra(t_main_cont *cont);
int		try_ra_dry_run(t_main_cont *cont);
bool	try_sa(t_main_cont *cont);
bool	try_sa_dry_run(t_main_cont *cont);
bool	try_pb(t_main_cont *cont);

//ERROR HANDLING
void	exit_on_err(char *err_message);

//UTILS
void	set_next_pos(int *pos, int size);
int		get_pos_in_stack(int *stack, int size, int value);
int		get_next_pos(int pos, int size);
bool	ft_assign_calloc(void **ptr, size_t count, size_t size);

//  PRINT UTILS
void	print_stacks(t_main_cont *cont);
void	print_single_stack(int *stack, int size);
void	print_move(int move);

//CLEANUP
void	cleanup(t_main_cont *cont);

//VECTORS
bool 	devec_init(t_vector *vector);
bool 	vec_add_back(t_vector *vector, int new_elem);
bool 	vec_add_front(t_vector *vector, int new_elem);
void	vec_remove_back(t_vector *vector);
void	vec_remove_front(t_vector *vector);
bool 	vec_resize_back(t_vector *vector, int new_size);
bool 	vec_resize_front(t_vector *vector, int new_size);
bool 	vec_free_list(t_vector *vector);
int		*vec_get_elems(t_vector *vector);
int		vec_get_size(t_vector *vector);
int		vec_get_elem(t_vector *vector, int pos);
void	vec_set_elem(t_vector *vector, int pos, int new_value);

#endif
