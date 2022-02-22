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
typedef struct s_stacks
{
	int	*malloced_space;
	int	*A;
	int	*B;
	int	size;
	int	sizeA;
	int	sizeB;
}	t_main_container;

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
void	parse(int argc, char *argv[], t_main_container *cont);
void	assign_inputs(char **args, t_main_container *cont, int size);
int		*normalize_stack_values(int *stack, int size);


//MOVES
void	rotate(int **stack, int size);
void	make_rab(int **stack, int size, int move);
void	rev_rotate(int **stack, int size);
void	make_rrab(int **stack, int size, int move);
void	swap(int *stack, int size);
void	make_sab(int *stack, int size, int move);
void	push(t_main_container *cont, int move);
void	make_push(t_main_container *cont, int move);

//SORTING
void	sort(t_main_container *cont);
void	sort_3(t_main_container *cont);
int		get_pos_smallest(int *stack, int size);
int		get_val_smallest(int *stack, int size);
int		get_val_biggest(int *stack, int size);
int		nb_sorted_at_pos(int *stack, int size, int pos);

//  SORT_5
void	sort_5(t_main_container *cont);
void	rotate_to_pos0(int **stack, int size, int pos);
void	insert_b(t_main_container *cont);
bool	try_rotate_and_swap(t_main_container *cont);
bool	try_ra(int *stack, int size);
bool	try_ra_dry_run(int *stack, int size);
bool	try_sa(t_main_container *cont);
bool	try_sa_dry_run(t_main_container *cont);
bool	try_pb(t_main_container *cont);

//ERROR HANDLING
void	exit_on_err(char *err_message);

//UTILS
void	print_stacks(t_main_container *cont);
void	print_single_stack(int *stack, int size);
void	print_move(int move);
void	set_next_index(int *pos, int size);

//CLEANUP
void	cleanup(t_main_container *cont);

#endif
