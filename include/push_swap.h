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

typedef struct s_deque t_deque;
typedef struct s_deque
{
	int		*elems;
	int		*malloced_space;
	int		nb_elems;
	int		min_elem;
	int		max_elem;
	int		capacity_total;
	int		capacity_after_head;
	int		capacity_before_head;
	bool	(*add_last)(t_deque *, int);
	bool	(*add_front)(t_deque *, int);
	void	(*remove_last)(t_deque *);
	void	(*remove_front)(t_deque *);
	bool	(*resize_last)(t_deque *, int);
	bool	(*resize_front)(t_deque *, int);
	void	(*free_list)(t_deque *);
	void	(*set_elem)(t_deque *, int, int);
	int		(*get_min_elem)(t_deque *);
	int		(*get_max_elem)(t_deque *);
}	t_deque;

//VECTORS
bool 	init_deque(t_deque *deque);
bool 	deque_add_last(t_deque *deque, int new_elem);
bool 	deque_add_front(t_deque *deque, int new_elem);
void	deque_remove_last(t_deque *deque);
void	deque_remove_front(t_deque *deque);
bool 	deque_resize_last(t_deque *deque, int new_size);
bool 	deque_resize_front(t_deque *deque, int new_size);
void 	deque_free_list(t_deque *deque);
void	deque_set_elem(t_deque *deque, int pos, int new_value);
int		deque_get_min_elem(t_deque *deque);
int		deque_get_max_elem(t_deque *deque);

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
	bool	is_reverse;
}	t_iterator;

void	set_iterator(t_iterator *iterator, int head, int size, bool direction);
void	set_iter_head(t_iterator *iterator, int new_head);
void	iterate(t_iterator *iterator);
void	iterate_once(t_iterator *iterator, bool is_reverse);
bool	iterate_n_loops(t_iterator *iterator, int n);

//TYPEDEFS
typedef struct s_main_cont
{
	t_deque	stack_a;
	t_deque	stack_b;
	t_deque	moves_list;
	t_iterator	pos_min_val_a;
	t_iterator	pos_min_val_b;
	t_iterator	pos_max_val_a;
	t_iterator	pos_max_val_b;
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
void	assign_inputs(t_main_cont *cont, char **args);
void	normalize_stack_values(t_deque *stack);


//MOVES
void	rotate(t_deque *stack);
void    do_ra(t_main_cont *cont, t_deque *moves_list);
void    do_rb(t_main_cont *cont, t_deque *moves_list);
void    do_rr(t_main_cont *cont, t_deque *moves_list);
void	rev_rotate(t_deque *stack);
void    do_rra(t_main_cont *cont, t_deque *moves_list);
void    do_rrb(t_main_cont *cont, t_deque *moves_list);
void    do_rrr(t_main_cont *cont, t_deque *moves_list);
void	swap(t_deque *stack);
void    do_sa(t_main_cont *cont, t_deque *moves_list);
void    do_sb(t_main_cont *cont, t_deque *moves_list);
void    do_ss(t_main_cont *cont, t_deque *moves_list);
void	push(t_deque *stack_src, t_deque *stack_dest);
void    do_pa(t_main_cont *cont, t_deque *moves_list);
void    do_pb(t_main_cont *cont, t_deque *moves_list);

//  Moves helper functions
static inline void	rotate_update_iterators(t_iterator *iterator);
static inline void	rev_rotate_update_iterators(t_iterator *iterator);
static inline void	swap_update_iterator(t_iterator *iterator);
static inline void	push_update_iterators(t_main_cont *cont);

//SORT
void	sort(t_main_cont *cont);

//  SORT UTILS
bool	is_sorted(t_deque *stack, int pos_smallest);
int		get_pos_smallest_val(t_deque *stack);
int		get_pos_biggest_val(t_deque *stack);
void	rotate_pos_in_a_to_0(t_main_cont *cont, t_deque *moves_list, int pos);
void	rotate_pos_in_b_to_0(t_main_cont *cont, t_deque *moves_list, int pos);

//  SORT_SMALL
void	sort_small(t_main_cont *cont);
bool	try_rotate(t_main_cont *cont);
// bool	try_swap(t_main_cont *cont, t_deque *smallest_moves_list);
// bool	try_pb(t_main_cont *cont, t_deque *smallest_moves_list);
// bool	try_invert4(t_main_cont *cont, t_deque *temp);

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
void    print_all_moves(t_deque *moves_list);
void	print_stacks_info(t_main_cont *cont);

//CLEANUP
void	cleanup(t_main_cont *cont);

#endif
