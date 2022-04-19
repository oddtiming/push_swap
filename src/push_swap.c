#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_main_cont	*cont;

	if (argc < 2)
		exit(EXIT_FAILURE);
	cont = ft_safealloc(sizeof(t_main_cont));
	parse(argc, argv, cont);
	if (cont->stack_a.size <= 7)
		sort(cont);

	assign_staying_and_leaving_vals(cont);

	int	i;
	int	div_depth_500 = 7;



	t_deque	*block_ids_a;
	t_deque	*block_ids_b;
	t_deque	*block_ids;
	int		nb_blocks;

	new_deque(&block_ids_a);
	new_deque(&block_ids_b);
	new_deque(&block_ids);


	cont->best_moves.size = INT_MAX;


	nb_blocks = 2;
	partition_leaving_vals_n_blocks(&cont->leaving_vals, block_ids_a, nb_blocks);

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
		copy_deque(&cont->initial_stack, &cont->stack_a);
		deque_reinit_list(&cont->stack_b);
	deque_reinit_list(&cont->curr_moves);
	deque_reinit_list(block_ids_b);


	nb_blocks = 3;
	partition_leaving_vals_n_blocks(&cont->leaving_vals, block_ids_a, nb_blocks);

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
		copy_deque(&cont->initial_stack, &cont->stack_a);
		deque_reinit_list(&cont->stack_b);
	copy_deque(&cont->initial_stack, &cont->stack_a);
	deque_reinit_list(&cont->stack_b);
	deque_reinit_list(&cont->curr_moves);
	deque_reinit_list(block_ids_b);


	nb_blocks = 4;
	partition_leaving_vals_n_blocks(&cont->leaving_vals, block_ids_a, nb_blocks);

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
		copy_deque(&cont->initial_stack, &cont->stack_a);
		deque_reinit_list(&cont->stack_b);
	copy_deque(&cont->initial_stack, &cont->stack_a);
	deque_reinit_list(&cont->stack_b);
	deque_reinit_list(&cont->curr_moves);
	deque_reinit_list(block_ids_b);


	nb_blocks = 5;
	partition_leaving_vals_n_blocks(&cont->leaving_vals, block_ids_a, nb_blocks);

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
		copy_deque(&cont->initial_stack, &cont->stack_a);
		deque_reinit_list(&cont->stack_b);
	copy_deque(&cont->initial_stack, &cont->stack_a);
	deque_reinit_list(&cont->stack_b);
	deque_reinit_list(&cont->curr_moves);
	deque_reinit_list(block_ids_b);


	nb_blocks = 6;
	partition_leaving_vals_n_blocks(&cont->leaving_vals, block_ids_a, nb_blocks);

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
		copy_deque(&cont->initial_stack, &cont->stack_a);
		deque_reinit_list(&cont->stack_b);
	copy_deque(&cont->initial_stack, &cont->stack_a);
	deque_reinit_list(&cont->stack_b);
	deque_reinit_list(&cont->curr_moves);
	deque_reinit_list(block_ids_b);




	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 13 / 24);
	insert_block_a(cont, block_ids, 0);
	insert_block_a(cont, block_ids, 1);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
		// undo_moves(cont, &cont->curr_moves);
		copy_deque(&cont->initial_stack, &cont->stack_a);
		deque_reinit_list(&cont->stack_b);
	copy_deque(&cont->initial_stack, &cont->stack_a);
	deque_reinit_list(&cont->stack_b);
	deque_reinit_list(&cont->curr_moves);


	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 5 / 8);
	insert_block_a(cont, block_ids, 0);
	insert_block_a(cont, block_ids, 1);
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


	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 11 / 24);
	insert_block_a(cont, block_ids, 1);
	insert_block_a(cont, block_ids, 0);
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


	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 9 / 24);
	insert_block_a(cont, block_ids, 1);
	insert_block_a(cont, block_ids, 0);
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


	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 3 / 5);
	insert_block_a(cont, block_ids, 1);
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
	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 1 / 2);
	insert_block_a(cont, block_ids, 1);
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
	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 2 / 5);
	insert_block_a(cont, block_ids, 1);
	insert_block_a(cont, block_ids, 0);
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


	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 3 / 5);
	insert_block_a(cont, block_ids, 1);
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
	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 2 / 5);
	insert_block_a(cont, block_ids, 1);
	insert_block_a(cont, block_ids, 0);
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


	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 3 / 5);
	insert_block_a(cont, block_ids, 1);
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
	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 1 / 2);
	insert_block_a(cont, block_ids, 1);
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
	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 1 / 2);
	insert_block_a(cont, block_ids, 1);
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
	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 2 / 5);
	insert_block_a(cont, block_ids, 1);
	insert_block_a(cont, block_ids, 0);
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


	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 1 / 2);
	insert_block_a(cont, block_ids, 0);
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
	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 1 / 2);
	insert_block_a(cont, block_ids, 0);
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
	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 1 / 2);
	insert_block_a(cont, block_ids, 0);
	insert_block_a(cont, block_ids, 1);
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




	partition_leaving_vals_cutoff(&cont->leaving_vals, block_ids, max_elem_leaving(cont, &cont->leaving_vals) * 7 / 24);
	insert_block_a(cont, block_ids, 1);
	insert_block_a(cont, block_ids, 0);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
		copy_deque(&cont->initial_stack, &cont->stack_a);
		deque_reinit_list(&cont->stack_b);
	deque_reinit_list(&cont->curr_moves);


	i = 0;
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
			// undo_moves(cont, &cont->curr_moves);
		copy_deque(&cont->initial_stack, &cont->stack_a);
		deque_reinit_list(&cont->stack_b);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}

	i = 0;
	while (i < div_depth_500)
	{
		try_n_divisions_closest(cont, block_ids, i);
		insert_last_block(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
			if (DEBUG)
				printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
		}
			// undo_moves(cont, &cont->curr_moves);
		copy_deque(&cont->initial_stack, &cont->stack_a);
		deque_reinit_list(&cont->stack_b);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}

	i = 0;
	while (i < div_depth_500)
	{
		try_n_divisions(cont, block_ids, i);
		insert_last_block(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
			if (DEBUG)
				printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
		}
		copy_deque(&cont->initial_stack, &cont->stack_a);
		deque_reinit_list(&cont->stack_b);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}

	i = 0;
	while (i < div_depth_500)
	{
		try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 7 / 24);
		insert_last_block(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
			if (DEBUG)
				printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
		}
		copy_deque(&cont->initial_stack, &cont->stack_a);
		deque_reinit_list(&cont->stack_b);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}


	print_all_moves(&cont->best_moves);
	cleanup(cont);

	// Free block_ids_a
	block_ids_a->free_list(block_ids_a);
	free(block_ids_a);

	// Free block_ids_b
	block_ids_b->free_list(block_ids_b);
	free(block_ids_b);

	// Free block_ids
	block_ids->free_list(block_ids);
	free(block_ids);

	return (EXIT_SUCCESS);
}
