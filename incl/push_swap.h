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

//TYPEDEFS
typedef struct s_stacks
{
	int	*A;			//NEEDS TO BE FREED
	int	*B;			//NEEDS TO BE FREED
	int	size;
}	t_stacks;

//PARSING
void	parse(int argc, char *argv[], t_stacks *stacks);

//INIT
void	init(char **args, t_stacks *stacks, int size);

//ERROR HANDLING
void	exit_on_err(char *err_message);

#endif
