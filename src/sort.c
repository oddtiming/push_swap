#include "push_swap.h"

void	sort_big(t_main_cont *cont)
{
	assign_longest_increasing_subsequence(cont);
	split_in_blocks(cont);
	split_in_two(cont);
	ignore_lis(cont);
	return ;
}

void	sort_small(t_main_cont *cont)
{
	if (cont->stack_a.size == 2 && !is_sorted(&cont->stack_a, 0))
		do_sa(cont, &cont->best_moves);
	else
		try_sort_small(cont);
	return ;
}

void	sort(t_main_cont *cont)
{
	if (cont->stack_a.size <= 7)
		sort_small(cont);
	else
		sort_big(cont);
	return ;
}

//Stopped here b/c Bernard is on his way
//I'm at: the else in try_sort_small at the end of the while is an error
//Then need to test behaviour for single stack 4 3 2 1 0 ==> should do invert_4