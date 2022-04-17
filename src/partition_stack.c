#include "push_swap.h"

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

void	partition_stack_in_two(t_deque *stack, t_deque *block_ids)
{
	int		i;

	deque_reinit_list(block_ids);
	i = 0;
	while (i < stack->size)
	{
		if (stack->elems[i] > stack->max_elem / 2)
			block_ids->add_last(block_ids, 1);
		else
			block_ids->add_last(block_ids, 0);
		i++;
	}
	return ;
}
