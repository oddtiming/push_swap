#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Works as expected. 
 * The iterator "class" itself doesn't malloc the iterator
 * 
 */


# define REVERSE 1
# define CANONICAL 0

typedef struct s_iterator
{
	int		index;
	int		head;
	int		max_size;
	int		prev_index;
	int		nb_loops;
	bool	is_reverse;
}	t_iterator;

void	set_iterator(t_iterator *iterator, int head, int size, bool direction);
void	iterate(t_iterator *iterator);
bool	iterate_one_loop(t_iterator *iterator);


void	set_iterator(t_iterator *iterator, int head, int size, bool direction)
{
	iterator->index = head;
	iterator->head = head;
	iterator->max_size = size;
	iterator->is_reverse = direction;
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
	incrementer = iterator->is_reverse * -1 + !iterator->is_reverse * 1;
	iterator->index += incrementer;
	if (incrementer == 1 && iterator->index > iterator->max_size - 1)
		iterator->index = 0;
	else if (incrementer == -1 && iterator->index < 0)
		iterator->index = iterator->max_size - 1;
	return ;
}

//Will return true as long as it's not done doing a full loop
bool	iterate_one_loop(t_iterator *iterator)
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
	if (iterator->nb_loops == 1)
		return (false);
	return (true);
}

int	main(void)
{
	t_iterator	iterator;
	int 		size;
	int			head;

	size = 5;
	head = 0;
	set_iterator(&iterator, head, size, CANONICAL);
	while (iterate_one_loop(&iterator))
	{
		printf("curr_index = %d\n", iterator.index);
		printf("prev_index = %d\n\n", iterator.prev_index);
	}
	return (0);
}