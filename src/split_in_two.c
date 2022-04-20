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

void	try_single_cutoff(t_main_cont *cont, t_deque *block_ids, float cutoff)
{
	partition_leaving_vals_cutoff(
		&cont->leaving_vals,
		block_ids,
		(int)(max_elem_leaving(cont, &cont->leaving_vals) * cutoff));
	insert_block_of_a_in_b(cont, block_ids, 0);
	insert_block_of_a_in_b(cont, block_ids, 1);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
		copy_deque(&cont->curr_moves, &cont->best_moves);
	copy_deque(&cont->initial_stack, &cont->stack_a);
	deque_reinit_list(&cont->stack_b);
	deque_reinit_list(&cont->curr_moves);
	return ;
}

void	split_in_two(t_main_cont *cont)
{
	t_deque	*block_ids;
	int		i;

	new_deque(&block_ids);

	try_single_cutoff(cont, block_ids, 5 / 8);
	try_single_cutoff(cont, block_ids, 13 / 24);
	try_single_cutoff(cont, block_ids, 11 / 24);
	try_single_cutoff(cont, block_ids, 3 / 8);
	try_single_cutoff(cont, block_ids, 7 / 24);


	partition_leaving_vals_cutoff(
		&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 3 / 5);
	insert_block_of_a_in_b(cont, block_ids, 1);
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
	partition_leaving_vals_cutoff(
		&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 1 / 2);
	insert_block_of_a_in_b(cont, block_ids, 1);
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
	partition_leaving_vals_cutoff(
		&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 2 / 5);
	insert_block_of_a_in_b(cont, block_ids, 1);
	insert_block_of_a_in_b(cont, block_ids, 0);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
		// undo_moves(cont, &cont->curr_moves);
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


	partition_leaving_vals_cutoff(
		&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 3 / 5);
	insert_block_of_a_in_b(cont, block_ids, 1);
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
	partition_leaving_vals_cutoff(
		&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 2 / 5);
	insert_block_of_a_in_b(cont, block_ids, 1);
	insert_block_of_a_in_b(cont, block_ids, 0);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
		// undo_moves(cont, &cont->curr_moves);
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


	partition_leaving_vals_cutoff(
		&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 3 / 5);
	insert_block_of_a_in_b(cont, block_ids, 1);
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
	partition_leaving_vals_cutoff(
		&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 1 / 2);
	insert_block_of_a_in_b(cont, block_ids, 1);
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
	partition_leaving_vals_cutoff(
		&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 1 / 2);
	insert_block_of_a_in_b(cont, block_ids, 1);
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
	partition_leaving_vals_cutoff(
		&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 2 / 5);
	insert_block_of_a_in_b(cont, block_ids, 1);
	insert_block_of_a_in_b(cont, block_ids, 0);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
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


	partition_leaving_vals_cutoff(
		&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 1 / 2);
	insert_block_of_a_in_b(cont, block_ids, 0);
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
	partition_leaving_vals_cutoff(
		&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 1 / 2);
	insert_block_of_a_in_b(cont, block_ids, 0);
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
	partition_leaving_vals_cutoff(
		&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 1 / 2);
	insert_block_of_a_in_b(cont, block_ids, 0);
	insert_block_of_a_in_b(cont, block_ids, 1);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
		// undo_moves(cont, &cont->curr_moves);
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


	partition_leaving_vals_cutoff(
		&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 1 / 2);
	insert_block_of_a_in_b(cont, block_ids, 1);
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
	partition_leaving_vals_cutoff(
		&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 1 / 2);
	insert_block_of_a_in_b(cont, block_ids, 1);
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
	partition_leaving_vals_cutoff(
		&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 1 / 2);
	insert_block_of_a_in_b(cont, block_ids, 1);
	insert_block_of_a_in_b(cont, block_ids, 0);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
		// undo_moves(cont, &cont->curr_moves);
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

	// Free block_ids
	block_ids->free_list(block_ids);
	free(block_ids);

	return ;
}