#include "push_swap.h"

bool	try_rotate(t_main_cont *cont)
{
	int			pos_of_smallest_value;
	t_vector	*smallest_moves_list;

	smallest_moves_list = malloc(sizeof(t_vector));
	if (!smallest_moves_list)
		exit_on_err("smallest_moves_list malloc error\n");
	init_devec(smallest_moves_list);
	pos_of_smallest_value = is_sorted_at_pos(&cont->stack_a);
	if (pos_of_smallest_value < 0)
	{
		smallest_moves_list->free_list(smallest_moves_list);
		free(smallest_moves_list);
		return (0);
	}
	rotate_pos_in_a_to_0(cont, smallest_moves_list, pos_of_smallest_value);
	cont->moves_list = *smallest_moves_list;
	free(smallest_moves_list);
	return (1);
}

void	sort_small(t_main_cont *cont)
{
	// t_vector	*temp;

	if (try_rotate(cont))
		return ;
	// else if (try_swap(cont, smallest_moves_list))
	// 	smallest_nb_moves = smallest_moves_list->list.nb_elems;
	// else
	// {
	// 	try_pb(cont, smallest_moves_list);
	// 	smallest_nb_moves = smallest_moves_list->list.nb_elems;
	// 	try_invert4(cont, temp);
	// 	if (temp->list.nb_elems > smallest_nb_moves)
	// 	{
	// 		smallest_moves_list->free_list(smallest_moves_list);
	// 		smallest_moves_list = temp;
	// 	}
	// }
	return ;
}

void	sort(t_main_cont *cont)
{
	if (cont->stack_a.list.nb_elems < 10)
		sort_small(cont);
	return ;
}