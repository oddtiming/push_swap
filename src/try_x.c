#include "push_swap.h"

bool	try_solution(t_main_cont *cont, t_deque *moves_buff)
{
	if (is_sorted(&cont->stack_a, cont->head_a.index) && \
		moves_buff->size + cont->curr_moves.size < cont->min_nb_moves)
	{
		insert_b(cont, moves_buff);
		rotate_to_0_in_a(cont, moves_buff, cont->head_a.index);
		if (check_if_best_moves(cont, moves_buff))
		{
			discard_moves(cont, moves_buff);
			return (true);
		}
	}
	return (false);
}

void	discard_moves(t_main_cont *cont, t_deque *moves_buff)
{
	undo_moves(cont, moves_buff);
	moves_buff->free_list(moves_buff);
	free(moves_buff);
	return ;
}

//will return true if sorted or if nb_moves > min_nb_moves
bool	try_swap(t_main_cont *cont)
{
	t_deque	*moves_buff;
	int		curr_pos;

	curr_pos = 0;
	moves_buff = NULL;
	while (curr_pos < cont->stack_a.size)
	{
		new_deque(&moves_buff);
		rotate_to_0_in_a(cont, moves_buff, curr_pos);
		do_sa(cont, moves_buff);
		if (try_solution(cont, moves_buff))
			return (true);
		discard_moves(cont, moves_buff);
		curr_pos++;
	}
	if (DEBUG)
	{
		printf(RED"\t try_swap failed with %d elems\n"RESET_COL, cont->stack_a.size);
	}
	return (false);
}

bool	try_sort_small(t_main_cont *cont)
{
	t_deque	*moves_buff;		
	int		curr_pos;

	if (cont->stack_a.size == 4 && try_invert_4(cont))
		return (true);
	moves_buff = NULL;
	curr_pos = 0;
	while (curr_pos < cont->stack_a.size)
	{
		if (curr_pos == 2)
			(void) curr_pos;
		if (cont->curr_moves.size > 25)
			exit_on_err("curr_moves > 25 !?\n");
		if (DEBUG)
		{
			printf(CYAN"Starting try_sort_small\n"RESET_COL);
			printf(CYAN"Curr insert attempt: stack_a[%d] == %d\n"RESET_COL, curr_pos, cont->stack_a.elems[curr_pos]);
			print_stacks_info(cont);
		}
		new_deque(&moves_buff);
		if (try_solution(cont, moves_buff))
			return (true);
		if (try_swap(cont))
		{
			discard_moves(cont, moves_buff);
			return (true);
		}
		if (cont->stack_a.size <= 3)
		{
			if (DEBUG)
			{
				printf(RED"REACHED END OF SOLUTIONS WITH stack_b[0] = %d and stack_b[1] = %d\n"RESET_COL, \
					cont->stack_b.elems[0], cont->stack_b.elems[1]);
			}
			discard_moves(cont, moves_buff);
			return (false);
		}
		// push stack_b[curr_pos]
		rotate_to_0_in_a(cont, moves_buff, curr_pos);
		do_pb(cont, moves_buff);
		// commit the changes for the next recursion
		cat_deque(moves_buff, &cont->curr_moves);
		// If we've reached a good enough solution, stop searching
		if (try_sort_small(cont))
		{
			if (DEBUG)
			{
				printf(GREEN"%*stry_sort_small killing itself recursively\n"RESET_COL, (cont->stack_b.size + 1) * 3, "-->");
			}
			discard_moves(cont, moves_buff);
			return (true);
		}
		// undo the effects of the push
		undo_n_moves(cont, &cont->curr_moves, moves_buff->size);
		// reset the moves_buff for the curr iteration
		moves_buff->free_list(moves_buff);
		free(moves_buff);
		moves_buff = NULL;
		curr_pos++;
	}
	if (DEBUG)
	{
		printf(RED"\t try_sort_small failed with %d elems\n"RESET_COL, cont->stack_a.size);
	}
	return (false);
}

/**
 * 	I need my moves_buff to live exclusively in the context of the try_fct
 * 	I don't want it to affect what happens outside of it, because then I lose track
 * 	of what has been done in which subfunction.
 * 
 * In other words, a try_x() fct will take any current state of stacks and 
 * attempt to take it to completion. For now, some of my try_x() fcts can fail, b/c
 * they are attempting sorting methods that are mere attempts.
 * For big stacks of data, I will not have the luxury of trying algos that can
 * fail, so each try_x() fct will take its current solving pattern to completion, OR stop once
 * it's reached a bigger nb of moves than the current best result, to prevent unnecessary calculations.
 * There could also be a hard-coded minimum number of iterations at which to stop trying
 * 
 * MIN NB OF ITERATIONS: 
 * 	log[size]MAX_MOVES = x;
 * 	(size)^x = MAX_MOVES
 * 
 * =====> let x == 1.38
 * (100 ^ 1.38 == 575)
 * (500 ^ 1.38 == 5304)
 * 
 * For 5, I will keep the hard-coded 7 in, b/c I know the theoretical minimum is 8.
 * Calculating the theoretical min of 100 is pointless, b/c the chances of
 * this particular configuration being tested are ~0.
 * 
 * The way I see things, a small sorting algorithm should always return the best result,
 * but a big one cannot adopt the same tactic, because it's impossible to calculate all 
 * possibilities for 50! and up.
 * Big sorting algorithms should therefore focus on the best average outcome
 * 	
 * 
 * 	check_if_best_moves() should compare if the sum total of local temp and cont->curr_moves
 * 	is smaller than the curr_best_moves, and if so update curr_best_moves accordingly
 * 
 * 
 * moves_buff:	
 * 		moves that had to be done to the current stack, including 
 * 		but not limited to pushes that have been done and need to be commited 
 * 		before the next recursion takes place.
 * best_moves:
 * 		collection of moves that have the best outcome for the current algorithm.
 * moves_buff:
 * 		list of moves that exist only in the context of a specific fct.
 * 		if the fct is "successful", a check will be made with check_if_best_moves to see if
 * 		the moves_buff added to the moves_buff add up to fewer moves than previously
 * 		registered in best_moves
 * final_moves:
 * 		the final list of moves to be printed.
 * 		Assigned from the algo with the fewest resulting moves
 * 
 */

bool	try_invert_4(t_main_cont *cont)
{
	t_deque	*moves_buff;

	moves_buff = NULL;
	new_deque(&moves_buff);
	do_sa(cont, moves_buff);
	do_ra(cont, moves_buff);
	do_ra(cont, moves_buff);
	do_sa(cont, moves_buff);
	
	if (try_solution(cont, moves_buff))
	{
		if (DEBUG)
		{
			printf(GREEN"\t try_invert_4 succeeded\n"RESET_COL);
		}
		return (true);
	}
	if (DEBUG)
	{
		printf(RED"\t try_invert_4 failed\n"RESET_COL);
	}
	discard_moves(cont, moves_buff);
	return (false);
}
