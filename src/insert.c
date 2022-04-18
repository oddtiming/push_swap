#include "push_swap.h"

void	insert_b(t_main_cont *cont, t_deque *moves_buff)
{
	t_insert_info	*info;

	if (cont->stack_b.size <= 0)
		return ;
	info = ft_safealloc(sizeof(t_insert_info));
	// if b is not empty, init will also call update_insert_info()
	// init_insert_info(cont, info);
	info->b_info.pos = 0;
	info->min_cost = 1000;
	info->min_delta_insert = 1000;

	while (info->b_info.pos < cont->stack_b.size)
	{
		update_insert_info(cont, info);
		// Attempt to not try EVERY value, but only those that can result in fewer moves
		// if stack_b pos is further than min_moves, set pos to stack_b.size - min_cost
		if (info->b_info.pos > info->min_cost && 
				info->b_info.pos <= cont->stack_b.size - info->min_cost &&
				cont->stack_a.size + cont->stack_b.size >= 500)
			info->b_info.pos = cont->stack_b.size - info->min_cost;
		info->b_info.pos++;
	}

	insert_elem_b(cont, moves_buff, info);

	free(info);
	insert_b(cont, moves_buff);
	return ;
}

static void	insert_same_sign(
	t_main_cont *cont, t_deque *moves_buff, t_insert_info *info)
{
	if (info->a_info.dist0_best > 0 || info->b_info.dist0_best > 0)
	{
		while (info->min_cost-- > 0)
		{
			if (--info->a_info.dist0_best < 0)
				do_rb(cont, moves_buff);
			else if (--info->b_info.dist0_best < 0)
				do_ra(cont, moves_buff);
			else
				do_rr(cont, moves_buff);
		}
	}
	while (info->min_cost-- > 0)
	{
		if (++info->a_info.dist0_best > 0)
			do_rrb(cont, moves_buff);
		else if (++info->b_info.dist0_best > 0)
			do_rra(cont, moves_buff);
		else
			do_rrr(cont, moves_buff);
	}
	do_pa(cont, moves_buff);
}

static void	insert_same_direction(
	t_main_cont *cont, t_deque *moves_buff, t_insert_info *info)
{
	if (info->min_cost == info->a_info.pos_best ||
		info->min_cost == info->b_info.pos_best)
	{
		while (info->min_cost-- > 0)
		{
			if (--info->a_info.pos_best < 0)
				do_rb(cont, moves_buff);
			else if (--info->b_info.pos_best < 0)
				do_ra(cont, moves_buff);
			else
				do_rr(cont, moves_buff);
		}
	}
	while (info->min_cost-- > 0)
	{
		if (++info->a_info.revpos_best > 0)
			do_rrb(cont, moves_buff);
		else if (++info->b_info.revpos_best > 0)
			do_rra(cont, moves_buff);
		else
			do_rrr(cont, moves_buff);
	}
	do_pa(cont, moves_buff);
}

static void	insert_indep_directions(
	t_main_cont *cont, t_deque *moves_buff, t_insert_info *info)
{
	if (info->a_info.dist0_best >= 0)
		while (info->a_info.dist0_best-- > 0)
			do_ra(cont, moves_buff);
	else
		while (info->a_info.dist0_best++ < 0)
			do_rra(cont, moves_buff);
	if (info->b_info.dist0_best >= 0)
		while (info->b_info.dist0_best-- > 0)
			do_rb(cont, moves_buff);
	else
		while (info->b_info.dist0_best++ < 0)
			do_rrb(cont, moves_buff);
	do_pa(cont, moves_buff);

}

void	insert_elem_b(
	t_main_cont *cont, t_deque *moves_buff, t_insert_info *info)
{
	t_stack_insert_info	*a_info;
	t_stack_insert_info	*b_info;

	if (cont->stack_b.size <= 0)
		return ;
	a_info = &info->a_info;
	b_info = &info->b_info;
	if (ft_same_sign(a_info->dist0_best, b_info->dist0_best))
		insert_same_sign(cont, moves_buff, info);
	else if (get_cost_either_direction(info) < get_cost_indep_directions(info))
		insert_same_direction(cont, moves_buff, info);
	else
		insert_indep_directions(cont, moves_buff, info);
	return ;	
}

int	calc_delta_two_values(t_main_cont *cont, int val_a, int val_b)
{
	int	delta_insert;
	int	max_a;
	int	min_a; 
	int	max_b; 
	int	min_b;

	max_a = cont->stack_a.max_elem;
	min_a = cont->stack_a.min_elem;
	max_b = cont->stack_b.max_elem;
	min_b = cont->stack_b.min_elem;
	delta_insert = ft_abs(val_a - val_b); // is now equal to the diff between the two
	//if bigger than half the absolute diff
	if (delta_insert <= (ft_max(max_a, max_b) + 1) / 2)
		return (delta_insert);
	delta_insert = (max_a - val_a) + (val_b - min_b) + 1;
	if (val_b > val_a)
		delta_insert = (max_b - val_b) + (val_a - min_a) + 1;
	return (delta_insert);
}

//Need to add absolute distance from previous one
int	calc_delta_insert(t_main_cont *cont, t_insert_info *info)
{
	t_iterator	*iter;
	int			delta_insert;

	iter = malloc(sizeof(t_iterator));
	if (!iter)
		exit_on_err("calc_delta_insert: iter error\n");
	set_iterator(iter, info->a_info.pos, cont->stack_a.size, 1);
	iterate_once(iter, 1);
	delta_insert = calc_delta_two_values(
			cont,
			cont->stack_a.elems[iter->index],
			cont->stack_b.elems[iter->index]);
	delta_insert = ft_min(delta_insert, \
		calc_delta_two_values(cont, info->a_info.val, info->b_info.val));
	free(iter);
	return (delta_insert);
}
