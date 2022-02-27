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

void	set_iterator(t_iterator *iterator, int head, int size, bool direction)
{
	iterator->index = head;
	iterator->head = head;
	iterator->max_size = size;
	iterator->direction = direction;
	//Will be incremented in the first loop to set at 0 once iterate starts
	iterator->nb_loops = -1;
	iterator->prev_index = -1;
	return ;
}

void	iterate(t_iterator *iterator)
{
	int	incrementer;

	if (iterator->index == iterator->head)
		iterator->nb_loops += 1;
	iterator->prev_index = iterator->index;
	//-1 if direction == REVERSE, +1 if direction == CANONICAL
	incrementer = iterator->direction * -1 + !iterator->direction * 1;
	iterator->index += incrementer;
	if (incrementer == 1 && iterator->index > iterator->max_size - 1)
		iterator->index = 0;
	else if (incrementer == -1 && iterator->index < 0)
		iterator->index = iterator->max_size - 1;
	return ;
}

//Will return true as long as it hasn't finished a full loop
bool	iterate_one_loop(t_iterator *iterator)
{
	int			incrementer;
	// static bool	did_one_loop;

	if (iterator->index == iterator->head)
		iterator->nb_loops += 1;
	iterator->prev_index = iterator->index;
	//-1 if direction == REVERSE, +1 if direction == CANONICAL
	incrementer = iterator->direction * -1 + !iterator->direction * 1;
	iterator->index += incrementer;
	if (incrementer == 1 && iterator->index > iterator->max_size - 1)
		iterator->index = 0;
	else if (incrementer == -1 && iterator->index < 0)
		iterator->index = iterator->max_size - 1;
	if (iterator->nb_loops == 1 && iterator->prev_index == iterator->head)
		return (false);
	return (true);
}
