#include "push_swap.h"

void	print_stacks(t_main_cont *cont)
{
	int	*stack_a;
	int	*stack_b;
	int	size_a;
	int	size_b;
	int	i;

	printf("    |\033[38;5;5m [A] \033[0m|\033[38;5;6m [B] \033[0;0;0m|\n");
	printf("+---+-----+-----+\n");
	i = 0;
	stack_a = cont->stack_a.get_elems(&cont->stack_a);
	stack_b = cont->stack_b.get_elems(&cont->stack_b);
	size_a = cont->stack_a.get_size(&cont->stack_a);
	size_b = cont->stack_a.get_size(&cont->stack_b);
	while (i < size_a || i < size_b)
	{
		printf("|%-3d|", i);
		if (i < size_a)
			printf("\033[38;5;5m %-3d \033[0;0;0m", stack_a[i]);
		else
			printf("\t\033[0m|");
		if (i < size_b)
			printf("|\033[38;5;6m %-3d \033[0m|\n", stack_b[i]);
		else
			printf("|     |\n\033[0m");
		i++;
	}
	printf("+---+-----+-----+\n");
}
