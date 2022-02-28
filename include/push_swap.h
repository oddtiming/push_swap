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
# include "deques.h"
# include "moves.h"
# include "iterators.h"

//DEFINES
# define _ARGC_MIN 2
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
typedef struct s_main_cont	t_main_cont;
typedef struct s_main_cont
{
	t_deque		stack_a;
	t_deque		stack_b;
	t_deque		moves_list;
	t_iterator	pos_min_val_a;
	t_iterator	pos_min_val_b;
	t_iterator	pos_max_val_a;
	t_iterator	pos_max_val_b;
	void		(**reverse_fcts)(t_main_cont *, t_deque *);
}	t_main_cont;

//Functions
//PARSING
void	parse(int argc, char *argv[], t_main_cont *cont);
void	init(t_main_cont *cont, char **args);
void	normalize_stack_values(t_deque *stack);
void	init_reverse_moves_array(void (**array)(t_main_cont *, t_deque *));

//SORT
void	sort(t_main_cont *cont);

//  SORT UTILS
bool	is_sorted(t_deque *stack, int pos_smallest);
int		get_pos_of_val(t_deque  *stack, int val);
int		get_pos_smallest_val(t_deque *stack);
int		get_pos_biggest_val(t_deque *stack);
int		get_next_bigger(t_deque *stack, int curr_val);
void	rotate_pos_in_a_to_0(t_main_cont *cont, t_deque *moves_list, int pos);
void	rotate_pos_in_b_to_0(t_main_cont *cont, t_deque *moves_list, int pos);


//  SORT_SMALL
void	sort_small(t_main_cont *cont);
bool	try_rotate(t_main_cont *cont);
bool	try_swap(t_main_cont *cont);

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
