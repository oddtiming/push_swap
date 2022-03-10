#include "push_swap.h"

int	ft_sqrt(int nb)
{
	int	sqrt;

	if (nb <= 0)
		return (0);
	if (nb == 1)
		return (1);
	sqrt = nb / 2;
	while (nb / sqrt < sqrt)
	{
		if (4 * (nb / sqrt) < sqrt)
			sqrt /= 2;
		else
			sqrt--;
	}
	// if (sqrt * sqrt == nb)
		return (sqrt);
	// else
		// return (0);
}

t_deque	*assign_staying_vals_stack(t_main_cont *cont, int pos, int range)
{
	t_deque		*staying_vals;
	t_iterator	*iter;
	int			curr_max;
	int			nb_loops;

	if (DEBUG)
	{
		printf("entered assign_staying\n");
		printf(GREEN"==>range = %d\n", range);
		printf(GREEN"==> pos = %d\n"RESET_COL, pos);
		printf(GREEN"==> cont->stack_a.elems[%d] = %d\n"RESET_COL, pos, cont->stack_a.elems[pos]);
	}
	staying_vals = ft_safealloc(sizeof(t_deque));
	init_deque(staying_vals);
	iter = ft_safealloc(sizeof(t_iterator));
	set_iterator(iter, pos, cont->stack_a.size, 0);
	staying_vals->add_last(staying_vals, -1);
	curr_max = cont->stack_a.elems[iter->index];
	nb_loops = 0;
	iterate_once(iter, 0);
	while (iter->index != iter->head)
	{
		if ((cont->stack_a.elems[iter->index] > curr_max && \
			cont->stack_a.elems[iter->index] - curr_max <= range) || \
			(cont->stack_a.elems[iter->index] < curr_max && \
			cont->stack_a.elems[iter->index] + cont->stack_a.size - curr_max <= range))
		{
			if (cont->stack_a.elems[iter->index] < curr_max)
				nb_loops++;
			// if (nb_loops <= 1 && cont->stack_a.elems[iter->index] > cont->stack_a.elems[iter->head])
			if (nb_loops < 1)
			{
				// printf(GREEN"sorted\n"RESET_COL);
				// printf(MAGENTA"\t stack_a[%d] == %d\n"RESET_COL, iter->index, cont->stack_a.elems[iter->index]);
				// printf(MAGENTA"\t curr_max == %d\n"RESET_COL, curr_max);
				// printf(MAGENTA"nb_loops =  %d\n"RESET_COL, nb_loops);
				staying_vals->add_last(staying_vals, -1);
				curr_max = cont->stack_a.elems[iter->index];
			}
			else
				staying_vals->add_last(staying_vals, cont->stack_a.elems[iter->index]);
		}
		else
			staying_vals->add_last(staying_vals, cont->stack_a.elems[iter->index]);
		iterate_once(iter, 0);
	}

	while (pos-- > 0)
	{
		staying_vals->add_front(staying_vals, staying_vals->elems[staying_vals->size - 1]);
		staying_vals->remove_last(staying_vals);
	}


	free(iter);
	return (staying_vals);
}

t_deque	*get_staying_vals(t_main_cont *cont)
{
	t_iterator	*iter;
	int			range;
	int			range_best;
	int			nb_sorted_curr;
	int			nb_sorted_max;
	int			pos_sorted_max;
	int			val_sorted_max;
	int			curr_max;
	int			i;
	int			nb_loops;

	iter = ft_safealloc(sizeof(t_iterator));
	nb_sorted_max = 0;
	pos_sorted_max = 0;
	range_best = 0;
	val_sorted_max = cont->stack_a.elems[0];

	range = 5;
	while (range <= 25)
	{
		i = 0;
		while (i < cont->stack_a.size)
		{
			set_iterator(iter, i, cont->stack_a.size, 0);
			nb_sorted_curr = 0;
			curr_max = cont->stack_a.elems[iter->index];
			nb_loops = 0;
			while (iterate_n_loops(iter, 1))
			{
				if ((cont->stack_a.elems[iter->index] > curr_max && \
					cont->stack_a.elems[iter->index] - curr_max <= range) || \
					(cont->stack_a.elems[iter->index] < curr_max && \
					cont->stack_a.elems[iter->index] + cont->stack_a.size - curr_max <= range))
				{
					if (cont->stack_a.elems[iter->index] < curr_max)
						nb_loops++;
					if (nb_loops < 1)
					{
						curr_max = cont->stack_a.elems[iter->index];
						nb_sorted_curr++;
					}
				}
			}
			// printf("nb_sorted for range %d at pos %d = %d\n", range, i, nb_sorted_curr);
			if (nb_sorted_curr > nb_sorted_max)
			{
				nb_sorted_max = nb_sorted_curr;
				pos_sorted_max = i;
				val_sorted_max = cont->stack_a.elems[i];
				range_best = range;
			}
			i++;
		}
		range++;
	}
	
	if (DEBUG)
	{
		printf(GREEN"\t->range_best = %d\n", range_best);
		printf(GREEN"==> pos_best = %d\n"RESET_COL, pos_sorted_max);
		printf(GREEN"==> val_best = %d \n"RESET_COL, val_sorted_max);
		printf(GREEN"==> nb_sorted = %d\n\n"RESET_COL, nb_sorted_max);
	}

	free(iter);
	return (assign_staying_vals_stack(cont, pos_sorted_max, range_best));
}
