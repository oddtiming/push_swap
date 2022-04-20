#include "push_swap.h"

int	max_elem_leaving(t_main_cont *cont, t_deque *leaving_vals)
{
	int	i;
	int	max_elem;

	i = 0;
	max_elem = -1;
	while (i < leaving_vals->size)
	{
		if (leaving_vals->elems[i] > max_elem
				&& !is_in_stack(&cont->stack_b, leaving_vals->elems[i]))
			max_elem = leaving_vals->elems[i];
		i++;
	}
	return (max_elem);
}

static inline void	try_single_cutoff(
	t_main_cont *cont, t_deque *block_ids, float cutoff, int block_id)
{
	partition_leaving_vals_cutoff(
		&cont->leaving_vals,
		block_ids,
		(int)(max_elem_leaving(cont, &cont->leaving_vals) * cutoff));
	insert_block_of_a_in_b(cont, block_ids, block_id);
	insert_block_of_a_in_b(cont, block_ids, (block_id + 1) % 2);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
		copy_deque(&cont->curr_moves, &cont->best_moves);
	copy_deque(&cont->initial_stack, &cont->stack_a);
	deque_reinit_list(&cont->stack_b);
	deque_reinit_list(&cont->curr_moves);
	return ;
}

static inline void	try_multiple_cutoffs_body(
	t_main_cont *cont, t_deque *block_ids, float curr_cutoff, int block_id)
{
	int	i;

	partition_leaving_vals_cutoff(
		&cont->leaving_vals,
		block_ids,
		(int)max_elem_leaving(cont, &cont->leaving_vals) * curr_cutoff);
	insert_block_of_a_in_b(cont, block_ids, block_id);
	deque_reinit_list(&cont->leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(&cont->staying_vals, cont->stack_a.elems[i]))
		{
			cont->leaving_vals.add_last(
				&cont->leaving_vals,
				-1);
		}
		else
		{
			cont->leaving_vals.add_last(
				&cont->leaving_vals,
				cont->stack_a.elems[i]);
		}
		i++;
	}
}

static inline void	try_multiple_cutoffs_footer(
	t_main_cont *cont, t_deque *block_ids, float curr_cutoff, int block_id)
{
	int	i;

	partition_leaving_vals_cutoff(
		&cont->leaving_vals,
		block_ids,
		(int)max_elem_leaving(cont, &cont->leaving_vals) * curr_cutoff);
	insert_block_of_a_in_b(cont, block_ids, block_id);
	insert_block_of_a_in_b(cont, block_ids, (block_id + 1) % 2);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
		copy_deque(&cont->curr_moves, &cont->best_moves);
	copy_deque(&cont->initial_stack, &cont->stack_a);
	deque_reinit_list(&cont->stack_b);
	deque_reinit_list(&cont->curr_moves);
	deque_reinit_list(&cont->leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(&cont->staying_vals, cont->stack_a.elems[i]))
			cont->leaving_vals.add_last(&cont->leaving_vals, -1);
		else
			cont->leaving_vals.add_last(&cont->leaving_vals, cont->stack_a.elems[i]);
		i++;
	}
}

void	split_in_two(t_main_cont *cont)
{
	t_deque	*block_ids;

	new_deque(&block_ids);

	try_single_cutoff(cont, block_ids, 17 / 24, 0);
	try_single_cutoff(cont, block_ids, 16 / 24, 0);
	try_single_cutoff(cont, block_ids, 5 / 8, 0);
	try_single_cutoff(cont, block_ids, 14 / 24, 0);
	try_single_cutoff(cont, block_ids, 13 / 24, 0);
	try_single_cutoff(cont, block_ids, 12 / 24, 0);
	try_single_cutoff(cont, block_ids, 12 / 24, 1);
	try_single_cutoff(cont, block_ids, 11 / 24, 1);
	try_single_cutoff(cont, block_ids, 10 / 24, 1);
	try_single_cutoff(cont, block_ids, 3 / 8, 1);
	try_single_cutoff(cont, block_ids, 8 / 24, 1);
	try_single_cutoff(cont, block_ids, 7 / 24, 1);

	try_multiple_cutoffs_body(cont, block_ids, 3/5, 1);
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 1);
	try_multiple_cutoffs_footer(cont, block_ids, 2/5, 1);

	try_multiple_cutoffs_body(cont, block_ids, 3/5, 1);
	try_multiple_cutoffs_footer(cont, block_ids, 2/5, 1);

	try_multiple_cutoffs_body(cont, block_ids, 3/5, 1);
	try_multiple_cutoffs_footer(cont, block_ids, 2/5, 1);

	try_multiple_cutoffs_body(cont, block_ids, 3/5, 1);
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 1);
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 1);
	try_multiple_cutoffs_footer(cont, block_ids, 2/5, 1);

	try_multiple_cutoffs_body(cont, block_ids, 1/2, 0);
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 0);
	try_multiple_cutoffs_footer(cont, block_ids, 1/2, 0);

	try_multiple_cutoffs_body(cont, block_ids, 1/2, 1);
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 1);
	try_multiple_cutoffs_footer(cont, block_ids, 1/2, 1);
	
//added
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 1);
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 1);
	try_multiple_cutoffs_footer(cont, block_ids, 1/2, 0);
	
//added
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 1);
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 0);
	try_multiple_cutoffs_footer(cont, block_ids, 1/2, 1);

//added
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 0);
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 1);
	try_multiple_cutoffs_footer(cont, block_ids, 1/2, 1);

//added
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 0);
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 0);
	try_multiple_cutoffs_footer(cont, block_ids, 1/2, 1);
	
//added
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 0);
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 1);
	try_multiple_cutoffs_footer(cont, block_ids, 1/2, 0);

//added
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 1);
	try_multiple_cutoffs_body(cont, block_ids, 1/2, 0);
	try_multiple_cutoffs_footer(cont, block_ids, 1/2, 0);

	// Free block_ids
	block_ids->free_list(block_ids);
	free(block_ids);

	return ;
}