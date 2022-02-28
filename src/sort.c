#include "push_swap.h"

// bool	try_rotate(t_main_cont *cont)
// {
// 	t_deque	*smallest_moves_list;

// 	smallest_moves_list = malloc(sizeof(t_deque));
// 	if (!smallest_moves_list)
// 		exit_on_err("try_rotate: smallest_moves_list malloc error\n");
// 	init_deque(smallest_moves_list);
// 	if (!is_sorted(&cont->stack_a, cont->pos_min_val_a.index))
// 	{
// 		smallest_moves_list->free_list(smallest_moves_list);
// 		free(smallest_moves_list);
// 		return (false);
// 	}
// 	rotate_pos_in_a_to_0(cont, smallest_moves_list, cont->pos_min_val_a.index);
// 	cont->moves_list.free_list(&cont->moves_list);
// 	cont->moves_list = *smallest_moves_list;
// 	free(smallest_moves_list);
// 	return (true);
// }

bool	try_swap(t_main_cont *cont)
{
	t_iterator	iterator;

	set_iterator(&iterator, 0, cont->stack_a.nb_elems, CANONICAL);
	while (iterate_n_loops(&iterator, 1))
	{
		rotate_pos_in_a_to_0(cont, &cont->moves_list, iterator.index);
		do_sa(cont, &cont->moves_list);
		if (is_sorted(&cont->stack_a, cont->pos_min_val_a.index))
			return (true);
		undo_moves(cont, &cont->moves_list);
	}
	return (false);
}

void	sort_small(t_main_cont *cont)
{
	// t_deque	*temp;

	if (is_sorted(&cont->stack_a, cont->pos_min_val_a.index))
	{
		rotate_pos_in_a_to_0(cont, &cont->moves_list, cont->pos_min_val_a.index);
		return ;
	}
	else if (try_swap(cont))
		return ;
	// if (cont->stack_b.nb_elems > 0)
	// 	insert_b(cont);
	
	// else
	// {
	// 	try_pb(cont, smallest_moves_list);
	// 	smallest_nb_moves = smallest_moves_list.nb_elems;
	// 	try_invert4(cont, temp);
	// 	if (temp.nb_elems > smallest_nb_moves)
	// 	{
	// 		smallest_moves_list->free_list(smallest_moves_list);
	// 		smallest_moves_list = temp;
	// 	}
	// }
	return ;
}

void	sort(t_main_cont *cont)
{
	if (cont->stack_a.nb_elems < 10)
		sort_small(cont);
	return ;
}