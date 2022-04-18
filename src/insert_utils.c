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
