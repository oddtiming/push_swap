#include "push_swap.h"

// void	calc_by_index(t_main_cont *cont)
// {
// 	t_iterator	iter;
// 	int			curr_max_index;
// 	int			nb_indexed;
	
// 	set_iterator(&iter, cont->head_a.index, cont->stack_a.size, 0);
// 	curr_max_index = cont->stack_a.min_elem;
// 	nb_indexed = 0;
// 	while (iterate_n_loops(&iter, 1))
// 	{
// 		if 
// 	}
// }


void	sort_big(t_main_cont *cont)
{
	int	elem_0;
	int	initial_size;
	// int	elem_1;
	// int	elem_last;

	initial_size = cont->stack_a.size;
	
	// assign_divisions

	// insert_a needs to be ONLY called after segmentation

	while (cont->stack_a.size > initial_size / 2)
	{
		elem_0 = cont->stack_a.elems[0];
		// elem_1 = cont->stack_a.elems[1];
		// elem_last = cont->stack_a.elems[cont->stack_a.size - 1];
		if (elem_0 >= initial_size / 2 - 1)
			do_pb(cont, &cont->final_moves);
		else
			do_ra(cont, &cont->final_moves);
	}
	while (!is_sorted(&cont->stack_a, cont->head_a.index) && cont->stack_a.size > 3)
	{
		do_pb(cont, &cont->final_moves);
	}
	if (!is_sorted(&cont->stack_a, cont->head_a.index))
		do_sa(cont, &cont->final_moves);
	insert_b(cont, &cont->final_moves);
	rotate_to_0_in_a(cont, &cont->final_moves, cont->head_a.index);
}