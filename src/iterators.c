#include "push_swap.h"

/**
 * Works as expected. 
 * The iterator "class" itself doesn't malloc the iterator
 */

// typedef struct s_iterator
// {
	// int		head;
	// int		index;
	// int		prev_index;
	// int		max_size;
	// int		nb_loops;
	// bool	direction;
// }	t_iterator;

void	set_iterator(t_iterator *iterator, int head, int size, bool is_reverse)
{
	iterator->index = head;
	iterator->head = head;
	iterator->max_size = size;
	iterator->is_reverse = is_reverse;
	//Will be incremented in the first loop to set at 0 once iterate starts
	iterator->nb_loops = -1;
	iterator->prev_index = -1;
	return ;
}

void	iterate(t_iterator *iterator)
{
	int	incrementer;

	iterator->prev_index = iterator->index;
	//-1 if direction == REVERSE, +1 if direction == CANONICAL
	incrementer = iterator->is_reverse * -1 + !iterator->is_reverse * 1;
	iterator->index += incrementer;
	if (incrementer == 1 && iterator->index > iterator->max_size - 1)
		iterator->index = 0;
	else if (incrementer == -1 && iterator->index < 0)
		iterator->index = iterator->max_size - 1;
	return ;
}

void	iterate_once(t_iterator *iterator, bool is_reverse)
{
	iterator->is_reverse = is_reverse;
	iterate(iterator);
	return ;
}

//Will return true as long as it hasn't finished a full loop
bool	iterate_n_loops(t_iterator *iterator, int n)
{
	int			incrementer;
	// static bool	did_one_loop;

	if (iterator->index == iterator->head)
		iterator->nb_loops += 1;
	iterator->prev_index = iterator->index;
	//-1 if direction == REVERSE, +1 if direction == CANONICAL
	incrementer = iterator->is_reverse * -1 + !iterator->is_reverse * 1;
	iterator->index += incrementer;
	if (incrementer == 1 && iterator->index > iterator->max_size - 1)
		iterator->index = 0;
	else if (incrementer == -1 && iterator->index < 0)
		iterator->index = iterator->max_size - 1;
	if (iterator->nb_loops >= n && iterator->prev_index == iterator->head)
		return (false);
	return (true);
}
