#include "push_swap.h"

void	init(t_main_cont *cont, char **args)
{
	int	i;

	init_deque(&cont->stack_a);
	init_deque(&cont->stack_b);
	init_deque(&cont->curr_moves);
	init_deque(&cont->best_moves);
	init_deque(&cont->final_moves);
	cont->reverse_fcts = malloc(11 * sizeof(void *));
	if (!cont->reverse_fcts)
		exit_on_err("reverse_fcts_my_ass\n");
	i = -1;
	while (args[++i] != NULL)
		if (cont->stack_a.add_last(&cont->stack_a, ft_atoi(args[i])))
			exit_on_err("deque_add_last done fucked up\n");
	if (DEBUG)
	{
		printf(CYAN"BEFORE normalization\n"RESET_COL);
		print_stacks_info(cont);
	}
	normalize_stack_values(&cont->stack_a);

	if (DEBUG)
	{
		printf(CYAN"AFTER normalization\n"RESET_COL);
		print_stacks_info(cont);
	}

	set_iterator(&cont->head_a, get_pos_smallest_val(&cont->stack_a), \
			cont->stack_a.size, 0);
	set_iterator(&cont->head_b, 0, 0, 1);
	init_reverse_moves_array(cont->reverse_fcts);
	cont->min_nb_moves = INT_MAX;
	return ;
}

void	init_reverse_moves_array(void (**array)(t_main_cont *, t_deque *))
{
	array[REV_SA] = &do_sa;
	array[REV_SB] = &do_sb;
	array[REV_SS] = &do_ss;
	array[REV_RA] = &do_rra;
	array[REV_RB] = &do_rrb;
	array[REV_RR] = &do_rrr;
	array[REV_RRA] = &do_ra;
	array[REV_RRB] = &do_rb;
	array[REV_RRR] = &do_rr;
	array[REV_PA] = &do_pb;
	array[REV_PB] = &do_pa;
	return ;
}

void	normalize_stack_values(t_deque *stack)
{
	int	*normalized_stack;
	int	nb_smaller_values;
	int	pos_in_stack;
	int	i;

	normalized_stack = malloc(stack->size * sizeof(int));
	if (!normalized_stack)
		exit_on_err("Malloc back at it again");
	pos_in_stack = 0;
	while (pos_in_stack < stack->size)
	{
		nb_smaller_values = 0;
		i = -1;
		while (++i < stack->size)
			if (stack->elems[i] < stack->elems[pos_in_stack])
				nb_smaller_values++;
		normalized_stack[pos_in_stack] = nb_smaller_values;
		pos_in_stack++;
	}
	i = -1;
	while (++i < stack->size)
	{
		stack->add_last(stack, normalized_stack[i]);
		stack->remove_front(stack);
		if (DEBUG)
		{
			printf(CYAN"added %d\n"RESET_COL, normalized_stack[i]);
			print_single_stack(stack);
		}
	}
	free(normalized_stack);
	return ;
}
