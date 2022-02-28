#include "push_swap.h"

bool	try_swap(t_main_cont *cont)
{
	t_iterator	iterator;

	set_iterator(&iterator, 0, cont->stack_a.nb_elems, CANONICAL);
	while (iterate_n_loops(&iterator, 1))
	{
		rotate_pos_in_a_to_0(cont, &cont->moves_list, iterator.index);
		do_sa(cont, &cont->moves_list);
		if (is_sorted(&cont->stack_a, cont->pos_min_val_a.index))
		{
			rotate_pos_in_a_to_0(cont, &cont->moves_list, cont->pos_min_val_a.index);
			return (true);
		}
		undo_moves(cont, &cont->moves_list);
	}
	return (false);
}


//Here's the logic for insert_b:
//	Should be recursive and take a moves_list as a parameter;
//	for each iteration, the fct should:
//		- keep in store the positions for the N smallest nb_moves to insert
//		- Iterate through these N values to compare the outcomes recursively can be.
//		- undo the last_move if the 
//	at the end, the list with the smallest nb_moves is concatenated to cont's moves_list
// void	insert_b(t_main_cont *cont)
// {
// 	int	i;
// 	int	smallest_nb_moves;
	
// 	smallest_nb_moves = INT_MAX;
// 	i = 0;
// 	while (i < cont->stack_b.nb_elems)
// 	{
// 		//Will return the minimal number of moves to insert elems[i]
// 		calculate_insert_cost()
// 	}
// }

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