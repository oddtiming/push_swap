#include "push_swap.h"

//otherwise, will undo the list of moves passed as param
bool	check_if_best_moves(t_main_cont *cont, t_deque *temp_moves)
{
	if (!is_sorted(&cont->stack_a, cont->head_a.index))
	{
		if (DEBUG)
		{
			print_stacks_info(cont);
			exit_on_err("dat look sorted to you?\n");
		}
	}
	else if (cont->best_moves.malloced_space == NULL || \
			cont->curr_moves.size + temp_moves->size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
		cat_deque(temp_moves, &cont->best_moves);
		cont->min_nb_moves = cont->best_moves.size;
		if (cont->min_nb_moves <= 8)
		{
			if (DEBUG)
			{
				printf(RED"\t###############################\n"RESET_COL);
				printf(GREEN"\tStack sorted in 8 or less moves\n"RESET_COL);
				printf(RED"\t###############################\n"RESET_COL);
				print_stacks_info(cont);
			}
			return (true); /////////////////////// Only exit call, don't like it.
		}
		if (DEBUG)
		{
			printf(GREEN"BEST MOVES UPDATED:");
			print_all_moves(&cont->best_moves);
		}
	}
	undo_moves(cont, temp_moves);
	return (false);
}

void	sort_small(t_main_cont *cont)
{
	//check if already or almost already sorted
	try_solution(cont, &cont->curr_moves);
	try_sort_small(cont);
	copy_deque(&cont->best_moves, &cont->final_moves);
	return ;
}

void	sort(t_main_cont *cont)
{
	if (cont->stack_a.size < 10)
		sort_small(cont);
	return ;
}

//Stopped here b/c Bernard is on his way
//I'm at: the else in try_sort_small at the end of the while is an error
//Then need to test behaviour for single stack 4 3 2 1 0 ==> should do invert_4