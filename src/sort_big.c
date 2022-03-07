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



void	insert_block(t_main_cont *cont, t_deque *block_ids, int curr_block_id)
{
	while (block_id_is_in_a(block_ids, curr_block_id))
	{
		if (block_ids->elems[0] == curr_block_id)
		{
			do_pb(cont, &cont->curr_moves);
			if (DEBUG)
			{
				printf("curr_id == %d\n", curr_block_id);
				printf("pushed value == %d\n", cont->stack_b.elems[0]);
				
				print_stacks(cont);
			}
		}
		else
		{
			do_ra(cont, &cont->curr_moves);
			block_ids->add_last(block_ids, block_ids->elems[0]);
		}
		block_ids->remove_front(block_ids);
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