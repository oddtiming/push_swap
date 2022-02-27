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

//VECTORS (need to learn how to properly link multiple headers in Makefile)
//Learned structure from https://aticleworld.com/implement-vector-in-c/
//Decided to fuck it up of my own volition, though

typedef struct s_vector t_vector;
typedef struct s_vector
{
	int		*elems;
	int		*malloced_space;
	int		nb_elems;
	int		smallest_elem;
	int		biggest_elem;
	int		capacity_total;
	int		capacity_after_head;
	int		capacity_before_head;
	bool	(*add_back)(t_vector *, int);
	bool	(*add_front)(t_vector *, int);
	void	(*remove_back)(t_vector *);
	void	(*remove_front)(t_vector *);
	bool	(*resize_back)(t_vector *, int);
	bool	(*resize_front)(t_vector *, int);
	void	(*free_list)(t_vector *);
	void	(*set_elem)(t_vector *, int, int);
	int		(*get_smallest_elem)(t_vector *);
	int		(*get_biggest_elem)(t_vector *);
}	t_vector;

//VECTORS
bool 	init_devec(t_vector *vector);
bool 	vec_add_back(t_vector *vector, int new_elem);
bool 	vec_add_front(t_vector *vector, int new_elem);
void	vec_remove_back(t_vector *vector);
void	vec_remove_front(t_vector *vector);
bool 	vec_resize_back(t_vector *vector, int new_size);
bool 	vec_resize_front(t_vector *vector, int new_size);
void 	vec_free_list(t_vector *vector);
void	vec_set_elem(t_vector *vector, int pos, int new_value);
int		vec_get_smallest_elem(t_vector *vector);
int		vec_get_biggest_elem(t_vector *vector);

//ITERATORS (still need to learn how to link headers...)
# define REVERSE 1
# define CANONICAL 0

typedef struct s_iterator
{
	int		head;
	int		index;
	int		prev_index;
	int		max_size;
	int		nb_loops;
	bool	direction;
}	t_iterator;

void	set_iterator(t_iterator *iterator, int head, int size, bool direction);
void	iterate(t_iterator *iterator);
bool	iterate_one_loop(t_iterator *iterator);

//TYPEDEFS
typedef struct s_main_cont
{
	t_vector	stack_a;
	t_vector	stack_b;
	t_vector	moves_list;
	t_iterator	pos_smallest_a;
	t_iterator	pos_smallest_b;
	t_iterator	pos_biggest_a;
	t_iterator	pos_biggest_b;
}	t_main_cont;

typedef enum e_moves
{
	RA = 'r' << 8 | 'a' << 0,
	RB = 'r' << 8 | 'b' << 0,
	RR = 'r' << 8 | 'r' << 0,
	RRA = 'r' << 16 | 'r'<< 8 | 'a' << 0,
	RRB = 'r' << 16 | 'r'<< 8 | 'b' << 0,
	RRR = 'r' << 16 | 'r'<< 8 | 'r' << 0,
	SA = 's' << 8 | 'a' << 0,
	SB = 's' << 8 | 'b' << 0,
	SS = 's' << 8 | 's' << 0,
	PA = 'p' << 8 | 'a' << 0,
	PB = 'p' << 8 | 'b' << 0
}	t_moves;

//Functions
//PARSING
void	parse(int argc, char *argv[], t_main_cont *cont);
void	assign_inputs(t_main_cont *cont, char **args, int size);
void	normalize_stack_values(t_vector *stack);


//MOVES
void	rotate(t_vector *stack);
void	rev_rotate(t_vector *stack);
void	swap(t_vector *stack);
void	push(t_vector *stack_src, t_vector *stack_dest);
void    do_ra(t_main_cont *cont, t_vector *moves_list);
void    do_rb(t_main_cont *cont, t_vector *moves_list);
void    do_rr(t_main_cont *cont, t_vector *moves_list);
void    do_rra(t_main_cont *cont, t_vector *moves_list, int move);
void    do_rrb(t_main_cont *cont, t_vector *moves_list, int move);
void    do_rrr(t_main_cont *cont, t_vector *moves_list, int move);
void    do_push(t_main_cont *cont, t_vector *moves_list, int move);
void    do_swap(t_main_cont *cont, t_vector *moves_list, int move);

//SORT
void	sort(t_main_cont *cont);

//  SORT UTILS
int		is_sorted_at_pos(t_vector *stack);
int		get_pos_smallest_value(t_vector *stack);
int		get_pos_biggest_value(t_vector *stack);
void	rotate_pos_in_a_to_0(t_main_cont *cont, t_vector *moves_list, int pos);
void	rotate_pos_in_b_to_0(t_main_cont *cont, t_vector *moves_list, int pos);

//  SORT_SMALL
void	sort_small(t_main_cont *cont);
bool	try_rotate(t_main_cont *cont);
// bool	try_swap(t_main_cont *cont, t_vector *smallest_moves_list);
// bool	try_pb(t_main_cont *cont, t_vector *smallest_moves_list);
// bool	try_invert4(t_main_cont *cont, t_vector *temp);

//ERROR HANDLING
void	exit_on_err(char *err_message);

//UTILS
void	set_next_pos(int *pos, int size);
int		get_pos_in_stack(int *stack, int size, int value);
int		get_next_pos(int pos, int size);
bool	ft_assign_calloc(void **ptr, size_t count, size_t size);

//  PRINT UTILS
void	print_stacks(t_main_cont *cont);
void	print_move(int move);
void    print_all_moves(t_vector *moves_list);
void	print_stacks_info(t_main_cont *cont);

//CLEANUP
void	cleanup(t_main_cont *cont);

#endif
