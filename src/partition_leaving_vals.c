#include "push_swap.h"

t_deque	*get_leaving_vals_trimmed(t_deque *leaving_vals)
{
	t_deque	*trimmed_vals;
	int		*temp_array;
	int		i;

	temp_array = ft_safealloc(leaving_vals->size * sizeof(int));
	ft_memset(temp_array, -1, leaving_vals->size * 4);
	i = 0;
	while (i < leaving_vals->size)
	{
		if (leaving_vals->elems[i] != -1)
			temp_array[leaving_vals->elems[i]] = leaving_vals->elems[i];
		i++;
	}
	new_deque(&trimmed_vals);
	i = 0;
	while (i < leaving_vals->size)
	{
		if (temp_array[i] != -1)
			trimmed_vals->add_last(trimmed_vals, temp_array[i]);
		i++;
	}
	free (temp_array);
	return (trimmed_vals);
}

void	partition_leaving_vals_n_blocks(t_deque *leaving_vals, t_deque *block_ids, int nb_blocks)
{
	t_deque	*trimmed_vals;
	int		block_len;
	int		curr_block_id;
	int		curr_block_min;
	int		offset;
	int		i;
	
	trimmed_vals = get_leaving_vals_trimmed(leaving_vals);
	offset = trimmed_vals->size % nb_blocks;
	deque_reinit_list(block_ids);
	block_len = trimmed_vals->size / nb_blocks + ((offset-- > 0) * 1);
	curr_block_id = 0;
	curr_block_min = 0;
	i = 0;
	while (i < leaving_vals->size)
	{
		if (leaving_vals->elems[i] >= trimmed_vals->elems[0] && \
				leaving_vals->elems[i] <= trimmed_vals->elems[block_len - 1])
			block_ids->add_last(block_ids, curr_block_id);
		else
			block_ids->add_last(block_ids, leaving_vals->elems[i]);
		i++;
	}
	while (++curr_block_id < nb_blocks)
	{
		curr_block_min += block_len;
		block_len = trimmed_vals->size / nb_blocks + ((offset-- > 0) * 1);
		i = 0;
		while (i < leaving_vals->size)
		{
			if (leaving_vals->elems[i] >= trimmed_vals->elems[curr_block_min] && \
					leaving_vals->elems[i] <= trimmed_vals->elems[curr_block_min + block_len - 1])
				block_ids->add_last(block_ids, curr_block_id);
			else
				block_ids->add_last(block_ids, block_ids->elems[0]);
			block_ids->remove_front(block_ids);
			i++;
		}
	}
	trimmed_vals->free_list(trimmed_vals);
	free (trimmed_vals);
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
