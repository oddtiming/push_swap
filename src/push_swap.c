#include "push_swap.h"

bool	has_many_block_ids(t_deque *block_ids)
{
	int	i;
	int	first_block_id;

	if (!block_ids || !block_ids->size)
		return (false);
	i = 0;
	first_block_id = block_ids->elems[i];
	while (i < block_ids->size)
	{
		if (block_ids->elems[i] != first_block_id)
			return (false);
		i++;
	}
	return (true);
}

void	try_n_divisions(t_main_cont *cont, t_deque *block_ids, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		partition_stack(&cont->stack_a, block_ids);
		insert_block(cont, block_ids, NB_BLOCKS - 1);
		i++;
	}
	return ;
}

void	try_n_divisions_smallest(t_main_cont *cont, t_deque *block_ids, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		partition_stack(&cont->stack_a, block_ids);
		insert_block(cont, block_ids, 0);
		i++;
	}
	return ;
}

void	try_n_divisions_closest(t_main_cont *cont, t_deque *block_ids, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		partition_stack(&cont->stack_a, block_ids);
		insert_block(cont, block_ids, block_ids->elems[0]);
		i++;
	}
	return ;
}


int	main(int argc, char *argv[])
{
	t_main_cont	*cont;
	t_deque		*block_ids;
	int			div_depth_100 = 7;
	int			div_depth_500 = 9;

	(void)div_depth_100;
	(void)div_depth_500;
	cont = malloc(sizeof(t_main_cont));
	if (!cont)
		exit_on_err("t_main_cont malloc error");
	ft_bzero(cont, sizeof(t_main_cont));
	parse(argc, argv, cont);
	if (DEBUG)
	{
		printf("\n----After normalization----\n\n");
		print_stacks_info(cont);
	}
	block_ids = ft_safealloc(sizeof(t_deque));
	init_deque(block_ids);

	cont->best_moves.size = INT_MAX;
	int			i;

	i = 0;
	while (i < div_depth_500)
	{
		try_n_divisions_smallest(cont, block_ids, i);
		blind_push(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
		}
		undo_moves(cont, &cont->curr_moves);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}

	i = 0;
	while (i < div_depth_500)
	{
		try_n_divisions_closest(cont, block_ids, i);
		blind_push(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
		}
		undo_moves(cont, &cont->curr_moves);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}

	i = 0;
	while (i < div_depth_500)
	{
		try_n_divisions(cont, block_ids, i);
		blind_push(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
		}
		undo_moves(cont, &cont->curr_moves);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}

	//try inserting smallest
	// partition_stack_n_blocks(&cont->stack_a, block_ids, 5);
	// insert_block(cont, block_ids, 3);
	// partition_stack_n_blocks(&cont->stack_a, block_ids, 4);
	// insert_block(cont, block_ids, 3);
	partition_stack_n_blocks(&cont->stack_a, block_ids, 3);
	insert_block(cont, block_ids, 2);
	partition_stack_n_blocks(&cont->stack_a, block_ids, 3);
	insert_block(cont, block_ids, 2);
	partition_stack_n_blocks(&cont->stack_a, block_ids, 3);
	insert_block(cont, block_ids, 2);
	i = 0;
	while (i < div_depth_500 - 1)
	{
		// try_n_divisions_closest(cont, block_ids, i);
		try_n_divisions(cont, block_ids, i);
		blind_push(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
		}
		undo_moves(cont, &cont->curr_moves);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}
	
	partition_stack_n_blocks(&cont->stack_a, block_ids, 4);
	insert_block(cont, block_ids, 3);
	partition_stack_n_blocks(&cont->stack_a, block_ids, 4);
	insert_block(cont, block_ids, 3);
	partition_stack_n_blocks(&cont->stack_a, block_ids, 4);
	insert_block(cont, block_ids, 3);
	partition_stack_n_blocks(&cont->stack_a, block_ids, 4);
	insert_block(cont, block_ids, 3);
	i = 0;
	while (i < div_depth_500 - 1)
	{
		// try_n_divisions_closest(cont, block_ids, i);
		try_n_divisions(cont, block_ids, i);
		blind_push(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
		}
		undo_moves(cont, &cont->curr_moves);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}

	partition_stack_n_blocks(&cont->stack_a, block_ids, 4);
	insert_block(cont, block_ids, 3);
	i = 0;
	while (i < div_depth_500)
	{
		// try_n_divisions_closest(cont, block_ids, i);
		try_n_divisions(cont, block_ids, i);
		blind_push(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
		}
		undo_moves(cont, &cont->curr_moves);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}

	partition_stack_n_blocks(&cont->stack_a, block_ids, 3);
	insert_block(cont, block_ids, 2);
	partition_stack_n_blocks(&cont->stack_a, block_ids, 3);
	insert_block(cont, block_ids, 2);
	i = 0;
	while (i < div_depth_500)
	{
		// try_n_divisions_closest(cont, block_ids, i);
		try_n_divisions(cont, block_ids, i);
		blind_push(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
		}
		undo_moves(cont, &cont->curr_moves);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}

	partition_stack_n_blocks(&cont->stack_a, block_ids, 3);
	insert_block(cont, block_ids, 2);
	i = 0;
	while (i < div_depth_500)
	{
		// try_n_divisions_closest(cont, block_ids, i);
		try_n_divisions(cont, block_ids, i);
		blind_push(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
		}
		undo_moves(cont, &cont->curr_moves);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}

	partition_stack_n_blocks(&cont->stack_a, block_ids, 3);
	insert_block(cont, block_ids, 2);
	partition_stack_n_blocks(&cont->stack_a, block_ids, 4);
	insert_block(cont, block_ids, 3);
	i = 0;
	while (i < div_depth_500 - 1)
	{
		// try_n_divisions_closest(cont, block_ids, i);
		try_n_divisions(cont, block_ids, i);
		blind_push(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
		}
		undo_moves(cont, &cont->curr_moves);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}

	partition_stack_n_blocks(&cont->stack_a, block_ids, 3);
	insert_block(cont, block_ids, 2);
	partition_stack_n_blocks(&cont->stack_a, block_ids, 4);
	insert_block(cont, block_ids, 3);
	partition_stack_n_blocks(&cont->stack_a, block_ids, 4);
	insert_block(cont, block_ids, 3);
	i = 0;
	while (i < div_depth_500)
	{
		// try_n_divisions_closest(cont, block_ids, i);
		try_n_divisions(cont, block_ids, i);
		blind_push(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
		}
		undo_moves(cont, &cont->curr_moves);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}

	partition_stack_n_blocks(&cont->stack_a, block_ids, 4);
	insert_block(cont, block_ids, 3);
	partition_stack_n_blocks(&cont->stack_a, block_ids, 3);
	insert_block(cont, block_ids, 2);
	i = 0;
	while (i < div_depth_500)
	{
		// try_n_divisions_closest(cont, block_ids, i);
		try_n_divisions(cont, block_ids, i);
		blind_push(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
		}
		undo_moves(cont, &cont->curr_moves);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}


	partition_stack_n_blocks(&cont->stack_a, block_ids, 8);
	insert_block(cont, block_ids, 7);
	partition_stack_n_blocks(&cont->stack_a, block_ids, 7);
	insert_block(cont, block_ids, 6);
	partition_stack_n_blocks(&cont->stack_a, block_ids, 6);
	insert_block(cont, block_ids, 5);
	partition_stack_n_blocks(&cont->stack_a, block_ids, 5);
	insert_block(cont, block_ids, 4);
	partition_stack_n_blocks(&cont->stack_a, block_ids, 4);
	insert_block(cont, block_ids, 3);
	partition_stack_n_blocks(&cont->stack_a, block_ids, 3);
	insert_block(cont, block_ids, 2);
	i = 0;
	while (i < div_depth_500 - 3)
	{
		// try_n_divisions_closest(cont, block_ids, i);
		try_n_divisions(cont, block_ids, i);
		blind_push(cont, &cont->curr_moves);
		insert_b(cont, &cont->curr_moves);
		rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
		if (cont->curr_moves.size < cont->best_moves.size)
		{
			copy_deque(&cont->curr_moves, &cont->best_moves);
		}
		undo_moves(cont, &cont->curr_moves);
		deque_reinit_list(&cont->curr_moves);
		i++;
	}



	print_all_moves(&cont->best_moves);

	// sort(cont);

	// print_all_moves(&cont->final_moves);
	if (DEBUG)
	{
		print_stacks_info(cont);
	}

		// print_stacks_info(cont);

	cleanup(cont);
	block_ids->free_list(block_ids);
	free(block_ids);

	return (EXIT_SUCCESS);
}
