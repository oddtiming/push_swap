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
//
// FOR NOW, though, simply calculate which element is fastest to insert, mb recursively
void	insert_b(t_main_cont *cont)
{
	int	i;
	int	smallest_insert_cost;
	int	smallest_insert_pos;
	int	curr_insert_cost;
	int	curr_insert_value;
	
	smallest_insert_cost = INT_MAX;
	i = 0;
	while (i < cont->stack_b.nb_elems)
	{
		curr_insert_value = get_next_bigger(&cont->stack_a, cont->stack_b.elems[i]);
		//Will calculate the minimum distance between two points in two stacks
		//calculate_min_dist(cont, pos_in_a, pos_in_b)
		curr_insert_cost = calculate_min_dist(cont, get_pos_of_val(&cont->stack_a, curr_insert_value), i);
		if (curr_insert_cost < smallest_insert_cost)
		{
			smallest_insert_cost = curr_insert_cost;
			smallest_insert_pos = i;
		}
	}
	//do some rotate shit. Dunno, I'm getting tired
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