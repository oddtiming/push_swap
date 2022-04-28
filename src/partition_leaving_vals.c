/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition_leaving_vals.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:54:39 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/27 23:40:17 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	partition_leaving_vals_cutoff(
	t_deque *staying_vals, t_deque *block_ids, int cutoff)
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

t_deque	*get_leaving_vals_trimmed(t_deque *leaving_vals)
{
	t_deque	*trimmed_vals;
	int		*temp_array;
	int		i;

	temp_array = ft_xalloc(leaving_vals->size * sizeof(int));
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

void	assign_first_partition(
	t_deque *leaving_vals,
	t_deque *block_ids,
	t_deque *trimmed_vals,
	t_partition_info *info)
{
	int	i;

	i = 0;
	while (i < leaving_vals->size)
	{
		if (leaving_vals->elems[i] >= trimmed_vals->elems[0] && \
			leaving_vals->elems[i] <= trimmed_vals->elems[info->block_len - 1])
			block_ids->add_last(block_ids, info->curr_block_id);
		else
			block_ids->add_last(block_ids, leaving_vals->elems[i]);
		i++;
	}
}

void	assign_partitions(
	t_deque *leaving_vals,
	t_deque *block_ids,
	t_deque *trimmed_vals,
	t_partition_info *info)
{
	int	i;

	i = 0;
	info->curr_block_min += info->block_len;
	info->block_len = trimmed_vals->size / info->nb_blocks;
	info->block_len += ((info->offset-- > 0) * 1);
	while (i < leaving_vals->size)
	{
		if (leaving_vals->elems[i] >= trimmed_vals->elems[info->curr_block_min]
			&& leaving_vals->elems[i]
			<= trimmed_vals->elems[info->curr_block_min + info->block_len - 1])
			block_ids->add_last(block_ids, info->curr_block_id);
		else
			block_ids->add_last(block_ids, block_ids->elems[0]);
		block_ids->remove_front(block_ids);
		i++;
	}
}

void	partition_leaving_vals_n_blocks(
	t_deque *leaving_vals, t_deque *block_ids, int nb_blocks)
{
	t_deque				*trimmed_vals;
	t_partition_info	info;

	trimmed_vals = get_leaving_vals_trimmed(leaving_vals);
	info.offset = trimmed_vals->size % nb_blocks;
	deque_reinit_list(block_ids);
	info.block_len = trimmed_vals->size / nb_blocks;
	info.block_len += ((info.offset-- > 0) * 1);
	info.curr_block_id = 0;
	info.curr_block_min = 0;
	info.nb_blocks = nb_blocks;
	assign_first_partition(leaving_vals, block_ids, trimmed_vals, &info);
	while (++info.curr_block_id < nb_blocks)
		assign_partitions(leaving_vals, block_ids, trimmed_vals, &info);
	trimmed_vals->free_list(trimmed_vals);
	free (trimmed_vals);
	return ;
}
