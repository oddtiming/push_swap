#include "push_swap.h"

int	dist_in_either_direction(t_insert_info *info)
{
	return (ft_min(
			ft_max(info->a_info.pos_best, info->b_info.pos_best),
			ft_max(-info->a_info.revpos, -info->b_info.revpos)));
}

int	dist_independent_direction(t_insert_info *info)
{
	return (ft_abs(info->a_info.dist0_best) + ft_abs(info->b_info.dist0_best));
}
