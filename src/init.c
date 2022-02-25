#include "push_swap.h"

void	assign_inputs(t_main_cont *cont, char **args, int size)
{
	int	i;

	cont->size_total = size;
	if (DEBUG)
		printf("in assign_inputs size = %d\n", size);

	if (devec_init(&cont->a) == FAILURE)
		exit_on_err("Oopsie fucky in the vector department\n");
	if (devec_init(&cont->b) == FAILURE)
		exit_on_err("Oopsie fucky in the vector department\n");
	i = 0;
	while (args[i] != NULL)
	{
		if (cont->a.add_back(&cont->a, ft_atoi(args[i])))
		{
			cleanup(cont);
			exit_on_err("vec_add_back done fucked up\n");
		}
		i++;
	}
	cont->moves = NULL;
	return ;
}
