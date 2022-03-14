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
		insert_block_a(cont, block_ids, 1);
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
		partition_stack_in_two(&cont->stack_a, block_ids);
		insert_block_a(cont, block_ids, NB_BLOCKS - 1);
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
		partition_stack_in_two(&cont->stack_a, block_ids);
		insert_block_a(cont, block_ids, 0);
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
		partition_stack_in_two(&cont->stack_a, block_ids);
		insert_block_a(cont, block_ids, block_ids->elems[0]);
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
