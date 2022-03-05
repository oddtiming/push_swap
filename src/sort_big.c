#include "push_swap.h"

void	calc_by_index(t_main_cont *cont)
{
	t_iterator	iter;
	int			curr_max_index;
	int			nb_indexed;
	
	set_iterator(&iter, cont->head_a.index, cont->stack_a.size, 0);
	curr_max_index = cont->stack_a.min_elem;
	nb_indexed = 0;
	while (iterate_n_loops(&iter, 1))
	{
		
	}
}


void	sort_big(t_main_cont *cont)
{
	int	nb_staying_by_index;
	int	nb_staying_by_value;

	nb_staying_by_index = calc_by_index(cont);
	nb_staying_by_value = calc_by_value(cont);

}