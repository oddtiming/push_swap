#include "push_swap.h"

//otherwise, will undo the list of moves passed as param
bool	check_if_best_moves(t_main_cont *cont, t_deque *moves_buff)
{
	int	total_nb_moves;
	
	if (!is_sorted(&cont->stack_a, cont->head_a.index))
	{
		if (DEBUG)
		{
			print_stacks_info(cont);
			exit_on_err("dat look sorted to you?\n");
		}
		return (false);
	}
	total_nb_moves = cont->curr_moves.size;
	if (moves_buff)
		total_nb_moves += moves_buff->size;
	if (total_nb_moves < cont->min_nb_moves)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
		cat_deque(moves_buff, &cont->best_moves);
		cont->min_nb_moves = cont->best_moves.size;
		if (cont->min_nb_moves <= 7)
		{
			if (DEBUG)
			{
				printf(RED"\t########################\n"RESET_COL);
				printf(GREEN"\tStack sorted in %d moves\n"RESET_COL, cont->min_nb_moves);
				printf(RED"\t########################\n"RESET_COL);
				print_stacks(cont);
				print_all_moves(&cont->best_moves);
			}
			return (true);
		}
		else if (DEBUG)
		{
			printf(RED"\t##################\n"RESET_COL);
			printf(GREEN"\tBEST MOVES UPDATED\n");
			printf(RED"\t##################\n"RESET_COL);
			printf(GREEN);
			print_all_moves(&cont->best_moves);
			printf(RESET_COL);
			print_stacks(cont);
		}
	}
	return (false);
}

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
		// insert_b(cont, &cont->final_moves);
		// // sort_small(cont);
		// rotate_to_0_in_a(cont, &cont->final_moves, cont->head_a.index);
	}

	return ;
}

//Stopped here b/c Bernard is on his way
//I'm at: the else in try_sort_small at the end of the while is an error
//Then need to test behaviour for single stack 4 3 2 1 0 ==> should do invert_4