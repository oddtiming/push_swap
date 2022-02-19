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
//END OF REMOVE


//TYPEDEFS
typedef struct s_stacks
{
	int	*A;			//NEEDS TO BE FREED
	int	*B;			//NEEDS TO BE FREED
	int	size;
	int	sizeA;
	int	sizeB;
}	t_stacks;

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
void	parse(int argc, char *argv[], t_stacks *stacks);
void	assign_inputs(char **args, t_stacks *stacks, int size);
int		*normalize_stack_values(int *stack, int size);


//MOVES
// void	rotate(int *stack, int size, bool is_reverse);
// void	swap(int *stack, int size);
// void	push(int *stack_src, int *stack_dest, int *size_src, int *size_dest);
void	make_move(t_stacks *stacks, int move);

//SOLVING
void	sort(t_stacks *stacks);
void	sort_3(t_stacks *stacks);
int		nb_sorted_at_smallest(int *stack, int size, int *pos_smallest);
int		nb_sorted_at_pos(int *stack, int size, int pos);

//ERROR HANDLING
void	exit_on_err(char *err_message);

//UTILS
void		print_stacks(t_stacks *stacks);
void		print_move(int move);
int			nb_sorted(int *stack, int size);
// inline int	get_0(int *stack, int size);

//CLEANUP
void	cleanup(t_stacks *stacks);

#endif
