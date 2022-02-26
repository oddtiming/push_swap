#include "push_swap.h"

void	assign_inputs(t_main_cont *cont, char **args, int size)
{
	int	i;

	cont->size_total = size;
	if (DEBUG)
		printf("in assign_inputs size = %d\n", size);
	if (devec_init(&cont->stack_a) == FAILURE)
		exit_on_err("Oopsie fucky in the vector department\n");
	if (devec_init(&cont->stack_b) == FAILURE)
		exit_on_err("Oopsie fucky in the vector department\n");
	i = 0;
	while (args[i] != NULL)
	{
		if (cont->stack_a.add_back(&cont->stack_a, ft_atoi(args[i])))
		{
			cleanup(cont);
			exit_on_err("vec_add_back done fucked up\n");
		}
		i++;
	}
	normalize_stack_values(&cont->stack_a);
	cont->moves = NULL;
	return ;
}

void	normalize_stack_values(t_vector *stack)
{
	int	*normalized_stack;
	int	nb_smaller_values;
	int	pos_in_stack;
	int	i;

	normalized_stack = malloc(stack->list.nb_elems * sizeof(int));
	if (!normalized_stack)
		exit_on_err("Malloc back at it again");
	pos_in_stack = 0;
	while (pos_in_stack < stack->list.nb_elems)
	{
		nb_smaller_values = 0;
		i = -1;
		while (++i < stack->list.nb_elems)
			if (stack->list.elems[i] < stack->list.elems[pos_in_stack])
				nb_smaller_values++;
		normalized_stack[pos_in_stack] = nb_smaller_values;
		pos_in_stack++;
	}
	i = -1;
	while (++i < stack->list.nb_elems)
		stack->set_elem(stack, i, normalized_stack[i]);
	free(normalized_stack);
	return (normalized_stack);
}
