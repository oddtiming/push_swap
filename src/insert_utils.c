#include "push_swap.h"

int	get_cost_either_direction(t_insert_info *info)
{
	return (ft_min(
			ft_max(info->a_info.pos_best, info->b_info.pos_best),
			ft_max(-info->a_info.revpos, -info->b_info.revpos)));
}

int	get_cost_indep_directions(t_insert_info *info)
{
	return (ft_abs(info->a_info.dist0_best) + ft_abs(info->b_info.dist0_best));
}

// Will return the next bigger value in the index, or stack_x.min_elem
int		get_insert_val(t_deque *stack, int curr_val)
{
	int	pos;
	int	next_bigger;

	if (curr_val + 1 > stack->max_elem)
		return (stack->min_elem);
	next_bigger = curr_val + 1;
	pos = 0;
	while (pos < stack->size)
	{
		if (stack->elems[pos] == next_bigger)
			return (next_bigger);
		pos++;
	}
	return (get_insert_val(stack, curr_val + 1));
}
