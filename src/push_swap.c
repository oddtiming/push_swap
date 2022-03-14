#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_main_cont	*cont;
	// t_deque		*block_ids;
	int			i;
	int			div_depth_100 = 7;
	int			div_depth_500 = 3;

	(void)div_depth_100;
	(void)div_depth_500;
	cont = malloc(sizeof(t_main_cont));
	if (!cont)
		exit_on_err("t_main_cont malloc error");
	ft_bzero(cont, sizeof(t_main_cont));
	parse(argc, argv, cont);

	t_deque	*curr_staying_vals;
	t_deque	*best_staying_vals;
	t_deque	*staying_stack;



	i = 0;

	// check nb_sorted for every val.
	new_deque(&staying_stack);
	copy_deque(&cont->stack_a, staying_stack);
	new_deque(&best_staying_vals);
	while (i < cont->stack_a.size)
	{
		rotate_stack_to_0(staying_stack, get_pos_of_val(staying_stack, i));
		curr_staying_vals = get_staying_vals(staying_stack);
		// printf(CYAN"nb_staying_vals = %d [%d]\n"RESET_COL, curr_staying_vals->size, i);
		if (curr_staying_vals->size > best_staying_vals->size)
		{
			copy_deque(curr_staying_vals, best_staying_vals);
		}
		staying_stack->remove_front(staying_stack);
		staying_stack->add_front(staying_stack, staying_stack->size + i + 1);
		curr_staying_vals->free_list(curr_staying_vals);
		free (curr_staying_vals);
		i++;
	}
	// Normalize best_staying_vals
	i = 0;
	while (i < best_staying_vals->size)
	{
		if (best_staying_vals->elems[0] > cont->stack_a.max_elem)
			best_staying_vals->add_last(best_staying_vals, best_staying_vals->elems[0] - cont->stack_a.size - 1);
		else
			best_staying_vals->add_last(best_staying_vals, best_staying_vals->elems[0]);
		best_staying_vals->remove_front(best_staying_vals);
		i++;
	}

	//Free staying_stack
	staying_stack->free_list(staying_stack);
	free(staying_stack);

	//Assign leaving_vals.
	t_deque	*leaving_vals;

	new_deque(&leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
			leaving_vals->add_last(leaving_vals, -1);
		else
			leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
		i++;
	}


	if (DEBUG)
	{
		printf("\n----After get_staying_vals----\n\n");
		print_single_stack(leaving_vals);
	}


	t_deque	*block_ids_a;
	t_deque	*block_ids_b;
	t_deque	*block_ids;
	int		nb_blocks;

	new_deque(&block_ids_a);
	new_deque(&block_ids_b);
	new_deque(&block_ids);

	cont->best_moves.size = INT_MAX;


	nb_blocks = 2;
	partition_leaving_vals_n_blocks(leaving_vals, block_ids_a, nb_blocks);

	i = nb_blocks;
	while (--i >= 0)
		insert_block_set_ids(cont, block_ids_a, block_ids_b, i);
	i = 0;
	while (i < (nb_blocks - 1) * 2)
	{
		insert_block_b(cont, block_ids_b, i);
		i++;
	}
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);
	deque_reinit_list(block_ids_b);


	nb_blocks = 3;
	partition_leaving_vals_n_blocks(leaving_vals, block_ids_a, nb_blocks);

	i = nb_blocks;
	while (--i >= 0)
		insert_block_set_ids(cont, block_ids_a, block_ids_b, i);
	i = 0;
	while (i < (nb_blocks - 1) * 2)
	{
		insert_block_b(cont, block_ids_b, i);
		i++;
	}
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);
	deque_reinit_list(block_ids_b);


	nb_blocks = 4;
	partition_leaving_vals_n_blocks(leaving_vals, block_ids_a, nb_blocks);

	i = nb_blocks;
	while (--i >= 0)
		insert_block_set_ids(cont, block_ids_a, block_ids_b, i);
	i = 0;
	while (i < (nb_blocks - 2) * 2)
	{
		insert_block_b(cont, block_ids_b, i);
		i++;
	}
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);
	deque_reinit_list(block_ids_b);




	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 13 / 24);
	insert_block_a(cont, block_ids, 0);
	insert_block_a(cont, block_ids, 1);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);


	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 5 / 8);
	insert_block_a(cont, block_ids, 0);
	insert_block_a(cont, block_ids, 1);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);


	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 11 / 24);
	insert_block_a(cont, block_ids, 1);
	insert_block_a(cont, block_ids, 0);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);


	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 9 / 24);
	insert_block_a(cont, block_ids, 1);
	insert_block_a(cont, block_ids, 0);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);


	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 3 / 5);
	insert_block_a(cont, block_ids, 1);
	deque_reinit_list(leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
			leaving_vals->add_last(leaving_vals, -1);
		else
			leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
		i++;
	}
	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 1 / 2);
	insert_block_a(cont, block_ids, 1);
	deque_reinit_list(leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
			leaving_vals->add_last(leaving_vals, -1);
		else
			leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
		i++;
	}
	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 2 / 5);
	insert_block_a(cont, block_ids, 1);
	insert_block_a(cont, block_ids, 0);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);
	deque_reinit_list(leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
			leaving_vals->add_last(leaving_vals, -1);
		else
			leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
		i++;
	}


	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 3 / 5);
	insert_block_a(cont, block_ids, 1);
	deque_reinit_list(leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
			leaving_vals->add_last(leaving_vals, -1);
		else
			leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
		i++;
	}
	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 2 / 5);
	insert_block_a(cont, block_ids, 1);
	insert_block_a(cont, block_ids, 0);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);
	deque_reinit_list(leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
			leaving_vals->add_last(leaving_vals, -1);
		else
			leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
		i++;
	}


	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 3 / 5);
	insert_block_a(cont, block_ids, 1);
	deque_reinit_list(leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
			leaving_vals->add_last(leaving_vals, -1);
		else
			leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
		i++;
	}
	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 1 / 2);
	insert_block_a(cont, block_ids, 1);
	deque_reinit_list(leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
			leaving_vals->add_last(leaving_vals, -1);
		else
			leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
		i++;
	}
	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 1 / 2);
	insert_block_a(cont, block_ids, 1);
	deque_reinit_list(leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
			leaving_vals->add_last(leaving_vals, -1);
		else
			leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
		i++;
	}
	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 2 / 5);
	insert_block_a(cont, block_ids, 1);
	insert_block_a(cont, block_ids, 0);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);
	deque_reinit_list(leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
			leaving_vals->add_last(leaving_vals, -1);
		else
			leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
		i++;
	}


	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 1 / 2);
	insert_block_a(cont, block_ids, 0);
	deque_reinit_list(leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
			leaving_vals->add_last(leaving_vals, -1);
		else
			leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
		i++;
	}
	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 1 / 2);
	insert_block_a(cont, block_ids, 0);
	deque_reinit_list(leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
			leaving_vals->add_last(leaving_vals, -1);
		else
			leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
		i++;
	}
	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 1 / 2);
	insert_block_a(cont, block_ids, 0);
	insert_block_a(cont, block_ids, 1);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);
	deque_reinit_list(leaving_vals);
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
			leaving_vals->add_last(leaving_vals, -1);
		else
			leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
		i++;
	}




	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 7 / 24);
	insert_block_a(cont, block_ids, 1);
	insert_block_a(cont, block_ids, 0);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);


	i = 0;
	// Try block with smallest values
	//	- insert_last_block
	while (i < div_depth_500)
	{
		try_n_divisions_smallest(cont, block_ids, 4);
		insert_last_block(cont, &cont->curr_moves);
		// blind_push(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
			if (DEBUG)
				printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
		}
		undo_moves(cont, &cont->curr_moves);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}

	i = 0;
	// Try closest block
	//	- insert_last_block
	while (i < div_depth_500)
	{
		try_n_divisions_closest(cont, block_ids, i);
		insert_last_block(cont, &cont->curr_moves);
		// blind_push(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
			if (DEBUG)
				printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
		}
		undo_moves(cont, &cont->curr_moves);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}

	i = 0;
	// Try block with biggest vals
	//	- insert_last_block
	while (i < div_depth_500)
	{
		try_n_divisions(cont, block_ids, i);
		insert_last_block(cont, &cont->curr_moves);
		// blind_push(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
			if (DEBUG)
				printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
		}
		undo_moves(cont, &cont->curr_moves);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}

	i = 0;
	while (i < div_depth_500)
	{
		try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 7 / 24);
		insert_last_block(cont, &cont->curr_moves);
		// blind_push(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
			if (DEBUG)
				printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
		}
		undo_moves(cont, &cont->curr_moves);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}

	// sort(cont);

	print_all_moves(&cont->best_moves);

	cleanup(cont);
	// staying_vals->free_list(staying_vals);
	// free (staying_vals);

	//Free block_ids
	// block_ids->free_list(block_ids);
	// free(block_ids);

	// Free block_ids_a
	block_ids_a->free_list(block_ids_a);
	free(block_ids_a);

	// Free block_ids_b
	block_ids_b->free_list(block_ids_b);
	free(block_ids_b);

	// Free block_ids
	block_ids->free_list(block_ids);
	free(block_ids);

	//Free leaving_stack
	leaving_vals->free_list(leaving_vals);
	free(leaving_vals);

	//Free best_staying_vals
	best_staying_vals->free_list(best_staying_vals);
	free(best_staying_vals);

	return (EXIT_SUCCESS);
}
