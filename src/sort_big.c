#include "push_swap.h"

// void	calc_by_index(t_main_cont *cont)
// {
// 	t_iterator	iter;
// 	int			curr_max_index;
// 	int			nb_indexed;
	
// 	set_iterator(&iter, cont->head_a.index, cont->stack_a.size, 0);
// 	curr_max_index = cont->stack_a.min_elem;
// 	nb_indexed = 0;
// 	while (iterate_n_loops(&iter, 1))
// 	{
// 		if 
// 	}
// }

typedef struct s_block_insert_info
{
	int	block_id_curr;
	int	block_id_best;
	int	spread_curr;
	int	spread_best;
}	t_block_insert_info;

bool	block_id_is_in_a(t_deque *block_ids, int id)
{
	int	i;

	i = 0;
	while (i < block_ids->size)
	{
		if(block_ids->elems[i] == id)
			return (true);
		i++;
	}
	return (false);
}

int	get_densest_block(t_deque *block_ids)
{
	int	pos_start;
	int	pos_end;
	int	min_spread;
	int	block_id;
	int	best_block_id;
	int	index;

	index = 0;
	pos_start = 0;
	block_id = NB_BLOCKS - 2;
	min_spread = INT_MAX;
	while (!block_id_is_in_a(block_ids, block_id))
		block_id--;
	while (block_id <= 0)
	{
		while (index < block_ids->size)
		{
			if (!pos_start && block_ids->elems[index] == block_id)
				pos_start = index;
			else if (block_ids->elems[index] == block_id)
				pos_end = index;
			index++;
		}
		if (ft_max(pos_end - pos_start, pos_start + block_ids->size - pos_end + 1) < min_spread)
		{
			min_spread = ft_max(pos_end - pos_start, pos_start + block_ids->size - pos_end + 1);
			best_block_id = block_id;
		}
		block_id--;
	}
	return (best_block_id);
}

void	rotate_block(t_main_cont *cont, t_deque *block_ids, int curr_block_id)
{
	int	pos_a;
	int	pos_b;
	int	revpos_b;
	int	insert_val_a;
	int	insert_val_b;

	pos_a = 0;
	while (block_ids->elems[pos_a] != curr_block_id)
		pos_a++;
	if (!cont->stack_b.size)
	{
		while (pos_a--)
		{
			do_ra(cont, &cont->curr_moves);
			block_ids->add_last(block_ids, block_ids->elems[0]);
			block_ids->remove_front(block_ids);
		}
		return ;
	}
	insert_val_a = cont->stack_a.elems[pos_a];
	insert_val_b = insert_val_a + 1;
	// pos_b = get_next_value(&cont->stack_b, insert_val_b + 2);
	
	pos_b = get_pos_of_val(&cont->stack_b, insert_val_b);
	while (pos_b == -1)
	{
		if (insert_val_b - 1 < cont->stack_b.min_elem)
		{
			insert_val_b = cont->stack_b.max_elem;
			pos_b = get_pos_of_val(&cont->stack_b, insert_val_b);
			break;
		}
		insert_val_b--;
		pos_b = get_pos_of_val(&cont->stack_b, insert_val_b);
	}
	revpos_b = cont->stack_b.size - pos_b;
	if (DEBUG)
	{
		printf("pos_a = %d\n", pos_a);
		printf("pos_b = %d\n", pos_b);
		printf("revpos_b = %d\n", revpos_b);
		printf("insert_val_b = %d\n", insert_val_b);
		printf("insert_val_a = %d\n", cont->stack_a.elems[pos_a]);
	}
	if ((pos_b - pos_a <= 0) || (pos_b - pos_a < revpos_b))
	{
		while (pos_a > 0)
		{
			pos_a--;
			if (pos_b >= 0)
			{
				do_rr(cont, &cont->curr_moves);
				block_ids->add_last(block_ids, block_ids->elems[0]);
				block_ids->remove_front(block_ids);
			}
			else
			{
				do_ra(cont, &cont->curr_moves);
				block_ids->add_last(block_ids, block_ids->elems[0]);
				block_ids->remove_front(block_ids);
			}
		}
	}
	else
		while (pos_a > 0)
		{
			do_ra(cont, &cont->curr_moves);
			block_ids->add_last(block_ids, block_ids->elems[0]);
			block_ids->remove_front(block_ids);
			pos_a--;
		}

	return ;
}

int	calc_block_median(t_deque *stack, t_deque *block_ids, int curr_block_id, int *max_val, int *min_val)
{
	int	median_val;
	int	curr_pos;

	median_val = 0;
	curr_pos = 0;
	while (curr_pos < stack->size)
	{
		if (block_ids->elems[curr_pos] == curr_block_id)
		{
			if (stack->elems[curr_pos] < *min_val)
				*min_val = stack->elems[curr_pos];
			else if (stack->elems[curr_pos] > *max_val)
				*max_val = stack->elems[curr_pos];
		}
		curr_pos++;
	}
	median_val = (*max_val - *min_val) / 2 + *min_val;
	return (median_val);
}

bool	has_smaller_than_median(t_deque *stack, int median_val, int min_val)
{
	int	curr_pos;

	curr_pos = 0;
	while (curr_pos < stack->size)
	{
		if (stack->elems[curr_pos] >= min_val && stack->elems[curr_pos] <= median_val)
			return (true);
		curr_pos++;
	}
	return (false);
}

void	rotate_block_split(t_main_cont *cont, t_deque *block_ids, int curr_block_id, int max_val, int min_val, int median_val)
{
	int	pos_a;
	
	pos_a = 0;
	while (block_ids->elems[pos_a] != curr_block_id)
		pos_a++;
	// if (pos_a && cont->stack_b.elems[0] >= median_val && cont->stack_b.elems[0] <= max_val)
	// {
	// 	do_rr(cont, &cont->curr_moves);
	// 	block_ids->add_last(block_ids, block_ids->elems[0]);
	// 	block_ids->remove_front(block_ids);
	// 	pos_a--;
	// }
	// if (cont->stack_b.elems[0] >= median_val && cont->stack_b.elems[0] <= max_val)
	// 	do_rb(cont, &cont->curr_moves);
	if (has_smaller_than_median(&cont->stack_b, median_val, min_val))
	{
		while (pos_a && cont->stack_b.elems[0] > median_val && cont->stack_b.elems[0] <= max_val)
		{
			do_rr(cont, &cont->curr_moves);
			block_ids->add_last(block_ids, block_ids->elems[0]);
			block_ids->remove_front(block_ids);
			pos_a--;
		}
		while (cont->stack_b.elems[0] > median_val && cont->stack_b.elems[0] <= max_val)
			do_rb(cont, &cont->curr_moves);

	}
	while (pos_a)
	{
		do_ra(cont, &cont->curr_moves);
		block_ids->add_last(block_ids, block_ids->elems[0]);
		block_ids->remove_front(block_ids);
		pos_a--;
	}
	// if ()
		// do_rr(cont, &cont->curr_moves);
	// 	else 
	// 		do_ra(cont, &cont->curr_moves);
	// 	block_ids->add_last(block_ids, block_ids->elems[0]);
	// 	block_ids->remove_front(block_ids);
	// }

	return ;
}

void	insert_block(t_main_cont *cont, t_deque *block_ids, int curr_block_id)
{
	int	median_val;
	int	max_val;
	int	min_val;

	max_val = 0;
	min_val = cont->stack_a.max_elem;
	median_val = calc_block_median(&cont->stack_a, block_ids, curr_block_id, &max_val, &min_val);
	while (block_id_is_in_a(block_ids, curr_block_id))
	{
		if (block_ids->elems[0] == curr_block_id)
		{
			do_pb(cont, &cont->curr_moves);
			// if (has_smaller_than_median(&cont->stack_b, median_val, min_val) && cont->stack_b.elems[0] > median_val && cont->stack_b.elems[0] <= max_val)
			// 		do_rb(cont, &cont->curr_moves);
			if (DEBUG)
			{
				printf("curr_id == %d\n", curr_block_id);
				printf("pushed value == %d\n", cont->stack_b.elems[0]);
				
				print_stacks(cont);
			}
			block_ids->remove_front(block_ids);
		}
		else
		{
			rotate_block_split(cont, block_ids, curr_block_id, max_val, min_val, median_val);
			// do_ra(cont, &cont->curr_moves);
			// block_ids->add_last(block_ids, block_ids->elems[0]);
		}
		while (has_smaller_than_median(&cont->stack_b, median_val, min_val) && cont->stack_b.elems[0] > median_val && cont->stack_b.elems[0] <= max_val)
			do_rb(cont, &cont->curr_moves);

		// block_ids->remove_front(block_ids);
	}
	return ;
}

void	print_stack_with_block_ids(int *stack, int *block_ids, int size)
{
	int	nb_each[NB_BLOCKS];
	int	i;

	i = 0;
	while (i < NB_BLOCKS)
		nb_each[i++] = 0;
	i = 0;
	while (i < size - 1)
	{
		printf("%3d|", stack[i]);
		i++;
	}
	printf("%3d\n", stack[i]);
	i = 0;
	while (i < size - 1)
	{
		printf("%3d|" , block_ids[i]);
		nb_each[block_ids[i]]++;
		i++;
	}
	printf("%3d\n\033[0m", block_ids[i]);
	nb_each[block_ids[i]]++;
	if (DEBUG)
	{
		i = 0;
		while (i < NB_BLOCKS)
		{
			printf("nb of vals in block %d: %d\n", i, nb_each[i]);
			i++;
		}
	}
	return ;
}

void	partition_stack(t_deque *stack, t_deque *block_ids)
{
	int		block_len;
	int		i;

	deque_reinit_list(block_ids);
	block_len = stack->size / NB_BLOCKS;
	i = 0;
	while (i < stack->size)
	{
		block_ids->add_last(block_ids, stack->elems[i] / block_len);
		if (block_ids->elems[i] == NB_BLOCKS)
			block_ids->set_elem(block_ids, i, NB_BLOCKS - 1);
		i++;
	}
	return ;
}

void	partition_leaving_vals_biggest(t_deque *staying_vals, t_deque *block_ids)
{
	int		cutoff;
	int		i;

	cutoff = staying_vals->max_elem * 7 / 24;
	deque_reinit_list(block_ids);
	i = 0;
	while (i < staying_vals->size)
	{
		if (staying_vals->elems[i] == -1)
			block_ids->add_last(block_ids, -1);
		else if (staying_vals->elems[i] > cutoff)
			block_ids->add_last(block_ids, 1);
		else 
			block_ids->add_last(block_ids, 0);
		i++;
	}
	return ;
}

void	partition_leaving_vals_cutoff(t_deque *staying_vals, t_deque *block_ids, int cutoff)
{
	int		i;

	deque_reinit_list(block_ids);
	i = 0;
	while (i < staying_vals->size)
	{
		if (staying_vals->elems[i] == -1)
			block_ids->add_last(block_ids, -1);
		else if (staying_vals->elems[i] > cutoff)
			block_ids->add_last(block_ids, 1);
		else 
			block_ids->add_last(block_ids, 0);
		i++;
	}
	return ;
}

void	partition_leaving_vals_smallest(t_deque *staying_vals, t_deque *block_ids)
{
	int		cutoff;
	int		i;

	cutoff = staying_vals->max_elem * 5 / 8;
	deque_reinit_list(block_ids);
	i = 0;
	while (i < staying_vals->size)
	{
		if (staying_vals->elems[i] == -1)
			block_ids->add_last(block_ids, -1);
		else if (staying_vals->elems[i] > cutoff)
			block_ids->add_last(block_ids, 1);
		else 
			block_ids->add_last(block_ids, 0);
		i++;
	}
	return ;
}

void	partition_stack_n_blocks(t_deque *stack, t_deque *block_ids, int nb_blocks)
{
	int		block_len;
	int		i;

	deque_reinit_list(block_ids);
	block_len = stack->size / nb_blocks;
	i = 0;
	while (i < stack->size)
	{
		block_ids->add_last(block_ids, stack->elems[i] / block_len);
		if (block_ids->elems[i] == nb_blocks)
			block_ids->set_elem(block_ids, i, nb_blocks - 1);
		i++;
	}
	return ;
}

void	partition_stack_cutoff(t_deque *stack, t_deque *block_ids, int cutoff)
{
	int		i;

	deque_reinit_list(block_ids);
	i = 0;
	while (i < stack->size)
	{
		if (stack->elems[i] > cutoff)
			block_ids->add_last(block_ids, 1);
		else
			block_ids->add_last(block_ids, 0);
		i++;
	}
	return ;
}

// void	try_divide(t_main_cont *cont, t_deque *moves_list)
// {
// 	// t_blk_insert_info	*info;
// 	int					*block_ids;
// 	int					curr_block_id;
 
// 	block_ids = partition_stack(cont->stack_a.elems, cont->stack_a.size);

// 	// curr_block_id = get_closest_block_id(block_ids, cont->stack_a.size);

// 	curr_block_id = block_ids[0];
// 	while (curr_block_id != 0)
// 	{
// 		insert_block(cont, block_ids, curr_block_id);
// 	}
// 	free(block_ids);
// }


void	sort_big(t_main_cont *cont)
{
	// int	elem_0;
	int	initial_size;
	// int	elem_1;
	// int	elem_last;

	initial_size = cont->stack_a.size;

	// if (stack->size == 100)
		// blind_push(cont, &cont->curr_moves);
	// else ()
	
	// assign_divisions

	// insert_a needs to be ONLY called after segmentation


	insert_b(cont, &cont->final_moves);
	rotate_to_0_in_a(cont, &cont->final_moves, cont->head_a.index);
}

void	insert_last_block(t_main_cont *cont, t_deque *moves_list)
{
	int	median_val;
	int	max_val;
	int	min_val;

	max_val = cont->stack_a.max_elem;
	min_val = cont->stack_a.min_elem;
	median_val = (max_val - min_val) / 2;
	while (cont->stack_a.size > 3)
	{
		do_pb(cont, &cont->curr_moves);
		if (has_smaller_than_median(&cont->stack_b, median_val, min_val) && cont->stack_b.elems[0] > median_val && cont->stack_b.elems[0] <= max_val)
			do_rb(cont, moves_list);
	}
	if (!is_sorted(&cont->stack_a, cont->head_a.index))
		do_sa(cont, moves_list);
	return ;

}


void	blind_push(t_main_cont *cont, t_deque *moves_list)
{
	while (!is_sorted(&cont->stack_a, cont->head_a.index) && cont->stack_a.size > 3)
	{
		do_pb(cont, moves_list);
	}
	if (!is_sorted(&cont->stack_a, cont->head_a.index))
		do_sa(cont, moves_list);
	return ;
}