#include "push_swap.h"

bool	try_solution(t_main_cont *cont, t_deque *temp_moves)
{
	if (is_sorted(&cont->stack_a, cont->head_a.index))
	{
		insert_b(cont, temp_moves);
		rotate_to_0_in_a(cont, temp_moves, cont->head_a.index);
		check_if_best_moves(cont, temp_moves);
		return (true);
	}
	return (false);
}

void	discard_moves(t_main_cont *cont, t_deque *temp_moves)
{
	undo_moves(cont, temp_moves);
	temp_moves->free_list(temp_moves);
	free(temp_moves);
}

bool	try_swap(t_main_cont *cont)
{
	t_deque	*temp_moves;
	int		curr_pos;

	curr_pos = 0;
	temp_moves = NULL;
	while (curr_pos < cont->stack_a.size)
	{
		new_deque(&temp_moves);
		rotate_to_0_in_a(cont, temp_moves, curr_pos);
		do_sa(cont, temp_moves);
		if (try_solution(cont, temp_moves))
		{
			discard_moves(cont, temp_moves);
			return (true);
		}
		discard_moves(cont, temp_moves);
		curr_pos++;
	}
	if (DEBUG)
	{
		printf(RED"\t try_swap failed with %d elems\n"RESET_COL, cont->stack_a.size);
	}
	return (false);
}

/////////////////////Switch the try_x to bool returns, and stop if they return true. to get rid of exit

bool	try_sort_small(t_main_cont *cont)
{
	t_deque	*temp_moves;		
	int		curr_pos;

	if ((cont->stack_a.size == 4) && try_invert_4(cont))
		return (true);
	temp_moves = NULL;
	curr_pos = 0;
	while (curr_pos < cont->stack_a.size)
	{
		if (DEBUG)
		{
			printf(CYAN"Starting try_sort_small\n"RESET_COL);
			printf(CYAN"Curr insert attempt: stack_a[%d] == %d\n"RESET_COL, curr_pos, cont->stack_a.elems[curr_pos]);
			print_stacks_info(cont);
		}
		new_deque(&temp_moves);
		if (try_swap(cont))
		{
			discard_moves(cont, temp_moves);
			return (true);
		}
		rotate_to_0_in_a(cont, temp_moves, curr_pos);
		do_pb(cont, temp_moves);
		//commit the changes for the next recursion
		cat_deque(temp_moves, &cont->curr_moves);
		try_sort_small(cont);
		//undo the effects of the push
		undo_n_moves(cont, &cont->curr_moves, temp_moves->size);
		//reset the temp_moves for the curr iteration
		discard_moves(cont, temp_moves);
		curr_pos++;
	}
	if (DEBUG)
	{
		printf(RED"\t try_sort_small failed with %d elems\n"RESET_COL, cont->stack_a.size);
	}
	return (false);
}

/**
 * 	I need my temp_moves to live exclusively in the context of the try_fct
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
 * temp_moves:	
 * 		moves that had to be done to the current stack, including 
 * 		but not limited to pushes that have been done and need to be commited 
 * 		before the next recursion takes place.
 * best_moves:
 * 		collection of moves that have the best outcome for the current algorithm.
 * temp_moves:
 * 		list of moves that exist only in the context of a specific fct.
 * 		if the fct is "successful", a check will be made with check_if_best_moves to see if
 * 		the temp_moves added to the temp_moves add up to fewer moves than previously
 * 		registered in best_moves
 * final_moves:
 * 		the final list of moves to be printed.
 * 		Assigned from the algo with the fewest resulting moves
 * 
 */

bool	try_invert_4(t_main_cont *cont)
{
	t_deque	*temp_moves;

	temp_moves = NULL;
	new_deque(&temp_moves);
	do_sa(cont, temp_moves);
	do_ra(cont, temp_moves);
	do_ra(cont, temp_moves);
	do_sa(cont, temp_moves);
	if (try_solution(cont, temp_moves))
	{
		if (DEBUG)
		{
			printf(GREEN"\t try_invert_4 succeeded\n"RESET_COL);
		}
		discard_moves(cont, temp_moves);
		return (true);
	}
	if (DEBUG)
	{
		printf(RED"\t try_invert_4 failed\n"RESET_COL);
	}
	discard_moves(cont, temp_moves);
	return (false);
}
