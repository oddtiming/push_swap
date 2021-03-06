#include "push_swap.h"

void	insert_same_sign(
	t_main_cont *cont, t_deque *block_ids_b, t_insert_info *info)
{
	if (info->a_info.dist0_best > 0 || info->b_info.dist0_best > 0)
	{
		while (info->min_cost-- > 0)
		{
			if (--info->b_info.dist0_best < 0)
				do_ra(cont, &cont->curr_moves);
			else
			{
				if (--info->a_info.dist0_best < 0)
					do_rb(cont, &cont->curr_moves);
				else
					do_rr(cont, &cont->curr_moves);
				block_ids_b->add_last(block_ids_b, block_ids_b->elems[0]);
				block_ids_b->remove_front(block_ids_b);
			}
		}
	}
	while (info->min_cost-- > 0)
	{
		if (++info->b_info.dist0_best > 0)
			do_rra(cont, &cont->curr_moves);
		else
		{
			if (++info->a_info.dist0_best > 0)
				do_rrb(cont, &cont->curr_moves);
			else
				do_rrr(cont, &cont->curr_moves);
			block_ids_b->add_front(block_ids_b, block_ids_b->elems[block_ids_b->size - 1]);
			block_ids_b->remove_last(block_ids_b);
		}
	}
	do_pa(cont, &cont->curr_moves);
	block_ids_b->remove_front(block_ids_b);
}


void	insert_same_direction(
	t_main_cont *cont, t_deque *block_ids_b, t_insert_info *info)
{
	if (info->min_cost == info->a_info.pos_best ||
		info->min_cost == info->b_info.pos_best)
	{
		while (info->min_cost-- > 0)
		{
			if (--info->b_info.pos_best < 0)
				do_ra(cont, &cont->curr_moves);
			else
			{
				if (--info->a_info.pos_best < 0)
					do_rb(cont, &cont->curr_moves);
				else
					do_rr(cont, &cont->curr_moves);
				block_ids_b->add_last(block_ids_b, block_ids_b->elems[0]);
				block_ids_b->remove_front(block_ids_b);
			}
		}
	}
	while (info->min_cost-- > 0)
	{
		if (++info->b_info.revpos_best > 0)
			do_rra(cont, &cont->curr_moves);
		else
		{
			if (++info->a_info.revpos_best > 0)
				do_rrb(cont, &cont->curr_moves);
			else
				do_rrr(cont, &cont->curr_moves);
			block_ids_b->add_front(block_ids_b, block_ids_b->elems[block_ids_b->size - 1]);
			block_ids_b->remove_last(block_ids_b);
		}
	}
	do_pa(cont, &cont->curr_moves);
	block_ids_b->remove_front(block_ids_b);
}


void	insert_indep_directions(
	t_main_cont *cont, t_deque *block_ids_b, t_insert_info *info)
{
	if (info->a_info.dist0_best >= 0)
		while (info->a_info.dist0_best-- > 0)
			do_ra(cont, &cont->curr_moves);
	else
		while (info->a_info.dist0_best++ < 0)
			do_rra(cont, &cont->curr_moves);
	if (info->b_info.dist0_best >= 0)
	{
		while (info->b_info.dist0_best-- > 0)
		{
			do_rb(cont, &cont->curr_moves);
			block_ids_b->add_last(block_ids_b, block_ids_b->elems[0]);
			block_ids_b->remove_front(block_ids_b);
		}
	}
	else
	{
		while (info->b_info.dist0_best++ < 0)
		{
			do_rrb(cont, &cont->curr_moves);
			block_ids_b->add_front(block_ids_b, block_ids_b->elems[block_ids_b->size - 1]);
			block_ids_b->remove_last(block_ids_b);
		}
	}
	do_pa(cont, &cont->curr_moves);
	block_ids_b->remove_front(block_ids_b);
}

void	insert_block_elem_b(
	t_main_cont *cont, t_deque *block_ids_b, t_insert_info *info)
{
	t_stack_insert_info	*a_info;
	t_stack_insert_info	*b_info;

	if (cont->stack_b.size <= 0)
		return ;
	a_info = &info->a_info;
	b_info = &info->b_info;
	if (cont->stack_b.size > 0)
	{
		//TO REMOVE
		// if (info.min_cost < 0)
		if (DEBUG && (info->min_cost < 0 || \
			(cont->stack_a.elems[0] > cont->stack_a.elems[1] && \
			cont->stack_a.elems[1] != cont->stack_a.min_elem)))
		{
			printf("wtf happened after\n");
			print_stacks(cont);
			printf(YELLOW"info.a_info.val_best = %d \n"RESET_COL, info->a_info.val_best);
			printf(YELLOW"info.a_info.pos_best = %d \n"RESET_COL, info->a_info.pos_best);
			printf(YELLOW"info.a_info.revpos_best = %d \n"RESET_COL, info->a_info.revpos_best);
			printf(YELLOW"info.b_info.val_best = %d \n"RESET_COL, info->b_info.val_best);
			printf(YELLOW"info.b_info.pos_best = %d \n"RESET_COL, info->b_info.pos_best);
			printf(YELLOW"info.b_info.revpos_best = %d \n"RESET_COL, info->b_info.revpos_best);
			printf(YELLOW"info.a_info.dist0_best = %d \n"RESET_COL, info->a_info.dist0_best);
			printf(YELLOW"info.b_info.dist0_best = %d \n"RESET_COL, info->b_info.dist0_best);
			printf(YELLOW"info.min_cost = %d \n"RESET_COL, info->min_cost);
			printf(YELLOW"info.min_delta_insert = %d \n"RESET_COL, info->min_delta_insert);
		}
		//EOREMOVE
	}
	// case for they both need to go in the same sense
	if (ft_same_sign(info->a_info.dist0_best, info->b_info.dist0_best))
		insert_same_sign(cont, block_ids_b, info);
	// case where their respective best rotations are in opposite directions,
	// but it's still better to move them in same direction
	else if (get_cost_either_direction(info) < get_cost_indep_directions(info))
		insert_same_direction(cont, block_ids_b, info);
	// case where they each do their own thing. that's okay too.
	else
		insert_indep_directions(cont, block_ids_b, info);
	return ;	
}


void	insert_block_of_b_in_a(t_main_cont *cont, t_deque *block_ids_b, int block_id)
{
	t_insert_info *info;

		// print_stacks(cont);
		// print_single_stack(block_ids_b);


	if (!block_id_is_in_stack(block_ids_b, block_id))
		return ;
	
	info = malloc(sizeof(t_insert_info));
	if (!info)
		exit_on_err("insert_b: insert_info error\n");

	info->min_cost = INT_MAX;
	info->min_delta_insert = INT_MAX;
	info->b_info.pos = 0;

	while (info->b_info.pos < block_ids_b->size)
	{
		if (block_ids_b->elems[info->b_info.pos] == block_id)
			update_insert_info(cont, info);
		info->b_info.pos++;
	}

	insert_block_elem_b(cont, block_ids_b, info);
	insert_block_of_b_in_a(cont, block_ids_b, block_id);

	//NEW
	free(info);
	info = NULL;
	return ;
}

void	insert_curr_block_id(
	t_main_cont *cont,
	t_deque *block_ids_a,
	t_deque *block_ids_b,
	t_block_info	*info)
{
	// if the first elem of stack_a is a candidate for push
	while (cont->stack_a.elems[0] <= info->median_val
		&& has_smaller_than_median(&cont->stack_b, info)
		&& cont->stack_b.elems[0] > info->median_val
		&& cont->stack_b.elems[0] <= info->max_val)
	{
		do_rb(cont, &cont->curr_moves);
		block_ids_b->add_last(block_ids_b, block_ids_b->elems[0]);
		block_ids_b->remove_front(block_ids_b);
	}
	do_pb(cont, &cont->curr_moves);
	if (cont->stack_b.elems[0] >= info->median_val)
		block_ids_b->add_front(block_ids_b, 1);
	else
		block_ids_b->add_front(block_ids_b, 0);
	block_ids_a->remove_front(block_ids_a);
}

void	rotate_to_block_id(
	t_main_cont *cont,
	t_deque *block_ids_a,
	t_deque *block_ids_b,
	t_block_info	*info)
{
	int	pos_a;

	pos_a = 0;
	while (block_ids_a->elems[pos_a] != info->curr_block_id)
		pos_a++;
	if (has_smaller_than_median(&cont->stack_b, info))
	{
		while (pos_a
			&& cont->stack_b.elems[0] > info->median_val
			&& cont->stack_b.elems[0] <= info->max_val)
		{
			do_rr(cont, &cont->curr_moves);
			
			block_ids_b->add_last(block_ids_b, block_ids_b->elems[0]);
			block_ids_b->remove_front(block_ids_b);

			block_ids_a->add_last(block_ids_a, block_ids_a->elems[0]);
			block_ids_a->remove_front(block_ids_a);
			pos_a--;
		}
	}
	while (pos_a)
	{
		do_ra(cont, &cont->curr_moves);
		block_ids_a->add_last(block_ids_a, block_ids_a->elems[0]);
		block_ids_a->remove_front(block_ids_a);
		pos_a--;
	}
	return ;
}

void	check_if_top_stack_b_is_smaller_than_median(
	t_main_cont *cont, t_deque *block_ids, t_block_info *info)
{
	while (cont->stack_b.elems[0] > info->median_val
		&& cont->stack_b.elems[0] <= info->max_val)
	{
		do_rb(cont, &cont->curr_moves);
		block_ids->add_last(block_ids, block_ids->elems[0]);
		block_ids->remove_front(block_ids);
	}
	return ;
}

void	insert_block_set_ids(
	t_main_cont *cont,
	t_deque *block_ids_a,
	t_deque *block_ids_b,
	int curr_block_id_a)
{
	t_block_info	info;
	int				i;

	info.curr_block_id = curr_block_id_a;
	info.max_val = 0;
	info.min_val = cont->stack_a.max_elem;
	assign_block_median(&cont->stack_a, block_ids_a, &info);
	i = 0;
	while (i < block_ids_b->size)
	{
		block_ids_b->elems[i] += 2;
		i++;
	}
	while (block_id_is_in_stack(block_ids_a, curr_block_id_a))
	{
		if (block_ids_a->elems[0] == curr_block_id_a)
			insert_curr_block_id(cont, block_ids_a, block_ids_b, &info);
		else
			rotate_to_block_id(cont, block_ids_a, block_ids_b, &info);
	}
	check_if_top_stack_b_is_smaller_than_median(cont, block_ids_b, &info);
	return ;
}
