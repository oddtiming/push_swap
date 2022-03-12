#include "push_swap.h"

int	max_elem_leaving(t_main_cont *cont, t_deque *leaving_vals)
{
	int	i;
	int	max_elem;

	i = 0;
	max_elem = -1;
	while (i < leaving_vals->size)
	{
		if (leaving_vals->elems[i] > max_elem && !is_in_stack(&cont->stack_b, leaving_vals->elems[i]))
			max_elem = leaving_vals->elems[i];
		i++;
	}
	return (max_elem);
}

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

void	try_cutoff_n(t_main_cont *cont, t_deque *block_ids, int n, int cutoff)
{
	int	i;

	i = 0;
	while (i < n)
	{
		partition_stack_cutoff(&cont->stack_a, block_ids, cutoff);
		insert_block(cont, block_ids, 1);
		i++;
	}
	return ;
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

void	print_staying_vals(t_main_cont *cont, t_deque *staying_vals)
{
	int	i;
	int	nb_sorted;

	nb_sorted = 0;
	i = 0;
	while (i < cont->stack_a.size)
	{
		printf(" [%2d] ", i);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < cont->stack_a.size)
	{
		printf(" %3d |", cont->stack_a.elems[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < cont->stack_a.size)
	{
		if (staying_vals->elems[i] == -1)
		{
			printf(GREEN" %3c |"RESET_COL, 'X');
			nb_sorted++;
		}
		else
			printf(RED" %3d |"RESET_COL, staying_vals->elems[i]);
		i++;
	}
	printf("\nnb_sorted = %d\n", nb_sorted);
}

int	main(int argc, char *argv[])
{
	t_main_cont	*cont;
	// t_deque		*block_ids;
	int			div_depth_100 = 7;
	int			div_depth_500 = 9;

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


	int	i;

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

	// copy_deque(leaving_vals, &cont->stack_b);
	// print_stacks(cont);

	// free(staying_vals);

	if (DEBUG)
	{
		printf("\n----After get_staying_vals----\n\n");
		print_single_stack(leaving_vals);
	}


	t_deque	*block_ids;
	// int		i;

	new_deque(&block_ids);

	cont->best_moves.size = INT_MAX;
	
	// deque_reinit_list(leaving_vals);
	// i = 0;
	// while (i < cont->stack_a.size)
	// {
	// 	if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
	// 		leaving_vals->add_last(leaving_vals, -1);
	// 	else
	// 		leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
	// 	i++;
	// }
	// partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 1 / 2);
	// insert_block(cont, block_ids, 1);
	// deque_reinit_list(leaving_vals);
	// i = 0;
	// while (i < cont->stack_a.size)
	// {
	// 	if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
	// 		leaving_vals->add_last(leaving_vals, -1);
	// 	else
	// 		leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
	// 	i++;
	// }
	// partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 1 / 2);
	// insert_block(cont, block_ids, 1);
	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 13 / 24);
	insert_block(cont, block_ids, 0);
	insert_block(cont, block_ids, 1);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);


	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 5 / 8);
	insert_block(cont, block_ids, 0);
	insert_block(cont, block_ids, 1);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);


	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 11 / 24);
	insert_block(cont, block_ids, 1);
	insert_block(cont, block_ids, 0);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);


	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 9 / 24);
	insert_block(cont, block_ids, 1);
	insert_block(cont, block_ids, 0);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);


	partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 3 / 5);
	insert_block(cont, block_ids, 1);
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
	insert_block(cont, block_ids, 1);
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
	insert_block(cont, block_ids, 1);
	insert_block(cont, block_ids, 0);
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
	insert_block(cont, block_ids, 0);
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
	insert_block(cont, block_ids, 0);
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
	insert_block(cont, block_ids, 0);
	insert_block(cont, block_ids, 1);
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




	// partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 7 / 24);
	// insert_block(cont, block_ids, 1);
	// insert_block(cont, block_ids, 0);
	// insert_b(cont, &cont->curr_moves);
	// rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	// if (cont->curr_moves.size < cont->best_moves.size)
	// {
	// 	copy_deque(&cont->curr_moves, &cont->best_moves);
	// 	if (DEBUG)
	// 		printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
	// }
	// undo_moves(cont, &cont->curr_moves);
	// deque_reinit_list(&cont->curr_moves);


	// deque_reinit_list(leaving_vals);
	// i = 0;
	// while (i < cont->stack_a.size)
	// {
	// 	if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
	// 		leaving_vals->add_last(leaving_vals, -1);
	// 	else
	// 		leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
	// 	i++;
	// }
	// partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 1 / 4);
	// insert_block(cont, block_ids, 1);

	// deque_reinit_list(leaving_vals);
	// i = 0;
	// while (i < cont->stack_a.size)
	// {
	// 	if (is_in_stack(best_staying_vals, cont->stack_a.elems[i]))
	// 		leaving_vals->add_last(leaving_vals, -1);
	// 	else
	// 		leaving_vals->add_last(leaving_vals, cont->stack_a.elems[i]);
	// 	i++;
	// }
	// partition_leaving_vals_cutoff(leaving_vals, block_ids, max_elem_leaving(cont, leaving_vals) * 5 / 24);
	// insert_block(cont, block_ids, 1);

	// blind_push(cont, &cont->curr_moves);
	// insert_b(cont, &cont->curr_moves);
	// rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	// print_stacks(cont);


	//Free best_staying_vals
	best_staying_vals->free_list(best_staying_vals);
	free(best_staying_vals);


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

	// i = 0;
	// // Try block with smallest values
	// //	- blind_push
	// while (i < div_depth_500)
	// {
	// 	try_n_divisions_smallest(cont, block_ids, 4);
	// 	// insert_last_block(cont, &cont->curr_moves);
	// 	blind_push(cont, &cont->curr_moves);
	// 	insert_b(cont, &cont->curr_moves);
	// 	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	// 	if (cont->curr_moves.size < cont->best_moves.size)
	// 	{
	// 		copy_deque(&cont->curr_moves, &cont->best_moves);
	// 		if (DEBUG)
	// 			printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
	// 	}
	// 	undo_moves(cont, &cont->curr_moves);
	// 	deque_reinit_list(&cont->curr_moves);
	// 	i++;
	// }

	// i = 0;
	// // Try closest block
	// //	- blind_push
	// while (i < div_depth_500)
	// {
	// 	try_n_divisions_closest(cont, block_ids, i);
	// 	// insert_last_block(cont, &cont->curr_moves);
	// 	blind_push(cont, &cont->curr_moves);
	// 	insert_b(cont, &cont->curr_moves);
	// 	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	// 	if (cont->curr_moves.size < cont->best_moves.size)
	// 	{
	// 		copy_deque(&cont->curr_moves, &cont->best_moves);
	// 		if (DEBUG)
	// 			printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
	// 	}
	// 	undo_moves(cont, &cont->curr_moves);
	// 	deque_reinit_list(&cont->curr_moves);
	// 	i++;
	// }

	// i = 0;
	// // Try block with biggest vals
	// //	- blind_push
	// while (i < div_depth_500)
	// {
	// 	try_n_divisions(cont, block_ids, i);
	// 	// insert_last_block(cont, &cont->curr_moves);
	// 	blind_push(cont, &cont->curr_moves);
	// 	insert_b(cont, &cont->curr_moves);
	// 	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	// 	if (cont->curr_moves.size < cont->best_moves.size)
	// 	{
	// 		copy_deque(&cont->curr_moves, &cont->best_moves);
	// 		if (DEBUG)
	// 			printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
	// 	}
	// 	undo_moves(cont, &cont->curr_moves);
	// 	deque_reinit_list(&cont->curr_moves);
	// 	i++;
	// }

	// i = 0;
	// while (i < div_depth_500)
	// {
	// 	try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 7 / 24);
	// 	insert_last_block(cont, &cont->curr_moves);
	// 	// blind_push(cont, &cont->curr_moves);
	// 	insert_b(cont, &cont->curr_moves);
	// 	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	// 	if (cont->curr_moves.size < cont->best_moves.size)
	// 	{
	// 		copy_deque(&cont->curr_moves, &cont->best_moves);
	// 		if (DEBUG)
	// 			printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
	// 	}
	// 	undo_moves(cont, &cont->curr_moves);
	// 	deque_reinit_list(&cont->curr_moves);
	// 	i++;
	// }

	// i = 0;
	// while (i < div_depth_500)
	// {
	// 	try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 2/5);
	// 	insert_last_block(cont, &cont->curr_moves);
	// 	// blind_push(cont, &cont->curr_moves);
	// 	insert_b(cont, &cont->curr_moves);
	// 	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	// 	if (cont->curr_moves.size < cont->best_moves.size)
	// 	{
	// 		copy_deque(&cont->curr_moves, &cont->best_moves);
	// 		if (DEBUG)
	// 			printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
	// 	}
	// 	undo_moves(cont, &cont->curr_moves);
	// 	deque_reinit_list(&cont->curr_moves);
	// 	i++;
	// }


	// i = 0;
	// while (i < div_depth_500)
	// {
	// 	try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 37 / 100);
	// 	insert_last_block(cont, &cont->curr_moves);
	// 	// blind_push(cont, &cont->curr_moves);
	// 	insert_b(cont, &cont->curr_moves);
	// 	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	// 	if (cont->curr_moves.size < cont->best_moves.size)
	// 	{
	// 		copy_deque(&cont->curr_moves, &cont->best_moves);
	// 		if (DEBUG)
	// 			printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
	// 	}
	// 	undo_moves(cont, &cont->curr_moves);
	// 	deque_reinit_list(&cont->curr_moves);
	// 	i++;
	// }

	// i = 0;
	// while (i < div_depth_500)
	// {
	// 	try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 1 / 4);
	// 	insert_last_block(cont, &cont->curr_moves);
	// 	// blind_push(cont, &cont->curr_moves);
	// 	insert_b(cont, &cont->curr_moves);
	// 	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	// 	if (cont->curr_moves.size < cont->best_moves.size)
	// 	{
	// 		copy_deque(&cont->curr_moves, &cont->best_moves);
	// 		if (DEBUG)
	// 			printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
	// 	}
	// 	undo_moves(cont, &cont->curr_moves);
	// 	deque_reinit_list(&cont->curr_moves);
	// 	i++;
	// }


	// i = 0;
	// while (i < div_depth_500)
	// {
	// 	try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 33 / 100);
	// 	insert_last_block(cont, &cont->curr_moves);
	// 	// blind_push(cont, &cont->curr_moves);
	// 	insert_b(cont, &cont->curr_moves);
	// 	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	// 	if (cont->curr_moves.size < cont->best_moves.size)
	// 	{
	// 		copy_deque(&cont->curr_moves, &cont->best_moves);
	// 		if (DEBUG)
	// 			printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
	// 	}
	// 	undo_moves(cont, &cont->curr_moves);
	// 	deque_reinit_list(&cont->curr_moves);
	// 	i++;
	// }




	// i = 0;
	// while (i < div_depth_500)
	// {
	// 	try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 31 / 100);
	// 	insert_last_block(cont, &cont->curr_moves);
	// 	// blind_push(cont, &cont->curr_moves);
	// 	insert_b(cont, &cont->curr_moves);
	// 	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	// 	if (cont->curr_moves.size < cont->best_moves.size)
	// 	{
	// 		copy_deque(&cont->curr_moves, &cont->best_moves);
	// 		if (DEBUG)
	// 			printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
	// 	}
	// 	undo_moves(cont, &cont->curr_moves);
	// 	deque_reinit_list(&cont->curr_moves);
	// 	i++;
	// }


	// i = 0;
	// while (i < div_depth_500)
	// {
	// 	try_cutoff_n(cont, block_ids, i, cont->stack_a.max_elem * 37 / 100);
	// 	insert_last_block(cont, &cont->curr_moves);
	// 	// blind_push(cont, &cont->curr_moves);
	// 	insert_b(cont, &cont->curr_moves);
	// 	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	// 	if (cont->curr_moves.size < cont->best_moves.size)
	// 	{
	// 		copy_deque(&cont->curr_moves, &cont->best_moves);
	// 		if (DEBUG)
	// 			printf(YELLOW"recursive_depth = %d\n"RESET_COL, i);
	// 	}
	// 	undo_moves(cont, &cont->curr_moves);
	// 	deque_reinit_list(&cont->curr_moves);
	// 	i++;
	// }


	// t_deque	*staying_vals;

	// staying_vals = ft_safealloc(sizeof(t_deque));
	// init_deque(staying_vals);
	// staying_vals = get_staying_vals(cont);

	// partition_leaving_vals_cutoff(staying_vals, block_ids, cont->stack_a.max_elem / 2);
	// insert_block(cont, block_ids, 1);
	// partition_leaving_vals_cutoff(staying_vals, block_ids, cont->stack_a.max_elem * 7/24);
	// insert_block(cont, block_ids, 1);
	// partition_leaving_vals_cutoff(staying_vals, block_ids, cont->stack_a.max_elem * 7/24);
	// insert_block(cont, block_ids, 1);
	// insert_block(cont, block_ids, 0);

	// insert_b(cont, &cont->curr_moves);
	// rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	// if (cont->curr_moves.size < cont->best_moves.size)
	// {
	// 	copy_deque(&cont->curr_moves, &cont->best_moves);
	// }
	// undo_moves(cont, &cont->curr_moves);
	// deque_reinit_list(&cont->curr_moves);


	// staying_vals->free_list(staying_vals);
	// free (staying_vals);


	// partition_stack_cutoff(&cont->stack_a, block_ids, cont->stack_a.max_elem / 2);
	// insert_block(cont, block_ids, 1);
	// partition_stack_cutoff(&cont->stack_a, block_ids, cont->stack_a.max_elem * 2 / 3);
	// insert_block(cont, block_ids, 1);
	// partition_stack_cutoff(&cont->stack_a, block_ids, cont->stack_a.max_elem * 2 / 3);
	// insert_block(cont, block_ids, 1);
	// insert_last_block(cont, &cont->curr_moves);
	// // blind_push(cont, &cont->curr_moves);
	// insert_b(cont, &cont->curr_moves);
	// rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	// if (cont->curr_moves.size < cont->best_moves.size)
	// {
	// 	copy_deque(&cont->curr_moves, &cont->best_moves);
	// }
	// undo_moves(cont, &cont->curr_moves);
	// deque_reinit_list(&cont->curr_moves);

	
	// partition_stack_cutoff(&cont->stack_a, block_ids, cont->stack_a.max_elem / 2);
	// insert_block(cont, block_ids, 1);
	// partition_stack_cutoff(&cont->stack_a, block_ids, cont->stack_a.max_elem * 2 / 3);
	// insert_block(cont, block_ids, 1);
	// partition_stack_cutoff(&cont->stack_a, block_ids, cont->stack_a.max_elem * 2 / 3);
	// insert_block(cont, block_ids, 1);
	// partition_stack_cutoff(&cont->stack_a, block_ids, cont->stack_a.max_elem * 2 / 3);
	// insert_block(cont, block_ids, 1);
	// partition_stack_cutoff(&cont->stack_a, block_ids, cont->stack_a.max_elem * 2 / 3);
	// insert_block(cont, block_ids, 1);
	// insert_last_block(cont, &cont->curr_moves);
	// // blind_push(cont, &cont->curr_moves);
	// insert_b(cont, &cont->curr_moves);
	// rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	// if (cont->curr_moves.size < cont->best_moves.size)
	// {
	// 	copy_deque(&cont->curr_moves, &cont->best_moves);
	// }
	// undo_moves(cont, &cont->curr_moves);
	// deque_reinit_list(&cont->curr_moves);

	
	partition_stack_cutoff(&cont->stack_a, block_ids, cont->stack_a.max_elem * 2 / 3);
	insert_block(cont, block_ids, 1);
	partition_stack_cutoff(&cont->stack_a, block_ids, cont->stack_a.max_elem / 2);
	insert_block(cont, block_ids, 1);
	partition_stack_cutoff(&cont->stack_a, block_ids, cont->stack_a.max_elem * 2 / 3);
	insert_block(cont, block_ids, 1);
	insert_last_block(cont, &cont->curr_moves);
	// blind_push(cont, &cont->curr_moves);
	insert_b(cont, &cont->curr_moves);
	rotate_to_0_in_a(cont, &cont->curr_moves, cont->head_a.index);
	if (cont->curr_moves.size < cont->best_moves.size)
	{
		copy_deque(&cont->curr_moves, &cont->best_moves);
	}
	undo_moves(cont, &cont->curr_moves);
	deque_reinit_list(&cont->curr_moves);


	print_all_moves(&cont->best_moves);

	// sort(cont);

	// print_all_moves(&cont->final_moves);
	// if (DEBUG)
	// {
	// 	print_stacks_info(cont);
	// }

		// print_stacks_info(cont);

	cleanup(cont);
	// staying_vals->free_list(staying_vals);
	// free (staying_vals);

	//Free block_ids
	block_ids->free_list(block_ids);
	free(block_ids);

	//Free leaving_stack
	leaving_vals->free_list(leaving_vals);
	free(leaving_vals);


	return (EXIT_SUCCESS);
}
