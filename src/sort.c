#include "push_swap.h"

void	sort_small(t_main_cont *cont)
{
	try_sort_small(cont);
	copy_deque(&cont->best_moves, &cont->final_moves);
	return ;
}

void	sort(t_main_cont *cont)
{
	if (cont->stack_a.size <= 7)
		sort_small(cont);
	else
	{
		sort_big(cont);
		// while (cont->stack_a.size != 3)
		// {
		// 	do_pb(cont, &cont->final_moves);
		// }

		// if (!is_sorted(&cont->stack_a, cont->head_a.index))
		// 	do_sa(cont, &cont->final_moves);
		// // sort_small(cont);
		// rotate_to_0_in_a(cont, &cont->final_moves, cont->head_a.index);
	}
	print_all_moves(&cont->final_moves);
	cleanup(cont);
	exit(EXIT_SUCCESS);
	return ;
}

//Stopped here b/c Bernard is on his way
//I'm at: the else in try_sort_small at the end of the while is an error
//Then need to test behaviour for single stack 4 3 2 1 0 ==> should do invert_4