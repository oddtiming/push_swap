#include "push_swap.h"

void	assign_inputs(t_main_cont *cont, char **args)
{
	int	i;

	if (init_devec(&cont->stack_a) == FAILURE)
		exit_on_err("Oopsie fucky in the vector department for stack_a\n");
	if (init_devec(&cont->stack_b) == FAILURE)
		exit_on_err("Oopsie fucky in the vector department for stack_b\n");
	if (init_devec(&cont->moves_list) == FAILURE)
		exit_on_err("Oopsie fucky in the vector department for moves_list\n");
	i = -1;
	while (args[++i] != NULL)
		if (cont->stack_a.add_back(&cont->stack_a, ft_atoi(args[i])))
			exit_on_err("vec_add_back done fucked up\n");
	normalize_stack_values(&cont->stack_a);
	set_iterator(&cont->pos_smallest_a, get_pos_smallest_val(&cont->stack_a), \
			cont->stack_a.nb_elems, CANONICAL);
	set_iterator(&cont->pos_biggest_a, get_pos_biggest_val(&cont->stack_a), \
			cont->stack_a.nb_elems, REVERSE);
	set_iterator(&cont->pos_smallest_b, 0, 0, CANONICAL);
	set_iterator(&cont->pos_biggest_b, 0, 0, REVERSE);
	return ;
}

void	normalize_stack_values(t_vector *stack)
{
	int	*normalized_stack;
	int	nb_smaller_values;
	int	pos_in_stack;
	int	i;

	normalized_stack = malloc(stack->nb_elems * sizeof(int));
	if (!normalized_stack)
		exit_on_err("Malloc back at it again");
	pos_in_stack = 0;
	while (pos_in_stack < stack->nb_elems)
	{
		nb_smaller_values = 0;
		i = -1;
		while (++i < stack->nb_elems)
			if (stack->elems[i] < stack->elems[pos_in_stack])
				nb_smaller_values++;
		normalized_stack[pos_in_stack] = nb_smaller_values;
		pos_in_stack++;
	}
	i = -1;
	while (++i < stack->nb_elems)
		stack->set_elem(stack, i, normalized_stack[i]);
	free(normalized_stack);
	return ;
}
