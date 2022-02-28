#ifndef ITERATORS_H
# define ITERATORS_H

# include "push_swap.h"


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

#endif