#include "iterators.h"

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

void	set_iter_head(t_iterator *iterator, int new_head)
{
	iterator->head = new_head;
	iterator->index = new_head;
	return ;
}

void	iterate(t_iterator *iterator)
{
	int	incrementer;

	iterator->prev_index = iterator->index;
	//-1 if direction == 1, +1 if direction == 0
	incrementer = iterator->is_reverse * -1 + !iterator->is_reverse * 1;
	iterator->index += incrementer;
	if (incrementer == 1 && iterator->index > iterator->max_size - 1)
		iterator->index = 0;
	else if (incrementer == -1 && iterator->index < 0)
		iterator->index = iterator->max_size - 1 * (iterator->max_size != 0);
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
	//-1 if direction == 1, +1 if direction == 0
	incrementer = iterator->is_reverse * -1 + !iterator->is_reverse * 1;
	iterator->index += incrementer;
	if (incrementer == 1 && iterator->index > iterator->max_size - 1)
		iterator->index = 0;
	else if (incrementer == -1 && iterator->index < 0)
		iterator->index = iterator->max_size - 1 * (iterator->max_size != 0);
	if (iterator->nb_loops >= n && iterator->index == iterator->head)
		return (false);
	return (true);
}
