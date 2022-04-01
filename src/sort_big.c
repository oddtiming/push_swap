#include "push_swap.h"

bool	block_id_is_in_stack(t_deque *block_ids, int id)
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
	insert_val_b = insert_val_a - 1;
	// pos_b = get_next_value(&cont->stack_b, insert_val_b + 2);
	
	pos_b = get_pos_of_val(&cont->stack_b, insert_val_b);
	while (pos_b == -1)
	{
		insert_val_b--;
		if (insert_val_b - 1 < cont->stack_b.min_elem)
		{
			insert_val_b = cont->stack_b.max_elem;
			pos_b = get_pos_of_val(&cont->stack_b, insert_val_b);
			break;
		}
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
	// if it's bringing it closer
	if (pos_b - pos_a < revpos_b)
	{
		while (pos_a > 0)
		{
			pos_a--;
			if (pos_b >= 0)
			{
				do_rr(cont, &cont->curr_moves);
				block_ids->add_last(block_ids, block_ids->elems[0]);
				block_ids->remove_front(block_ids);
				pos_b--;
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
	if (has_smaller_than_median(&cont->stack_b, median_val, min_val))
	{
		while (pos_a && cont->stack_b.elems[0] > median_val && cont->stack_b.elems[0] <= max_val)
		{
			do_rr(cont, &cont->curr_moves);
			block_ids->add_last(block_ids, block_ids->elems[0]);
			block_ids->remove_front(block_ids);
			pos_a--;
		}
	}
	while (pos_a)
	{
		do_ra(cont, &cont->curr_moves);
		block_ids->add_last(block_ids, block_ids->elems[0]);
		block_ids->remove_front(block_ids);
		pos_a--;
	}

	return ;
}

void	insert_block_a(t_main_cont *cont, t_deque *block_ids, int curr_block_id)
{
	int	median_val;
	int	max_val;
	int	min_val;

	max_val = 0;
	min_val = cont->stack_a.max_elem;
	median_val = calc_block_median(&cont->stack_a, block_ids, curr_block_id, &max_val, &min_val);
	if (DEBUG)
	{
		printf("in insert_block_a:\n block_id = %d\nmedian_val=%d\n", curr_block_id, median_val);
	}
	while (block_id_is_in_stack(block_ids, curr_block_id))
	{
		if (block_ids->elems[0] == curr_block_id)
		{
			while (cont->stack_a.elems[0] <= median_val && has_smaller_than_median(&cont->stack_b, median_val, min_val) && cont->stack_b.elems[0] > median_val && cont->stack_b.elems[0] <= max_val)
				do_rb(cont, &cont->curr_moves);
			do_pb(cont, &cont->curr_moves);
			// if (has_smaller_than_median(&cont->stack_b, median_val, min_val) && cont->stack_b.elems[0] > median_val && cont->stack_b.elems[0] <= max_val)
			// 		do_rb(cont, &cont->curr_moves);
			block_ids->remove_front(block_ids);
		}
		else
		{
			rotate_block_split(cont, block_ids, curr_block_id, max_val, min_val, median_val);
			// do_ra(cont, &cont->curr_moves);
			// block_ids->add_last(block_ids, block_ids->elems[0]);
		}
		// while (has_smaller_than_median(&cont->stack_b, median_val, min_val) && cont->stack_b.elems[0] > median_val && cont->stack_b.elems[0] <= max_val)
			// do_rb(cont, &cont->curr_moves);

		// block_ids->remove_front(block_ids);
	}
	while (cont->stack_b.elems[0] > median_val && cont->stack_b.elems[0] <= max_val)
		do_rb(cont, &cont->curr_moves);
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