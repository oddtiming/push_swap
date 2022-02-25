#include "push_swap.h"

void	print_stacks(t_main_cont *cont)
{
	int	*a;
	int	*b;
	int	size_a;
	int	size_b;
	int	i;

	printf("    |\033[38;5;5m [A] \033[0m|\033[38;5;6m [B] \033[0;0;0m|\n");
	printf("+---+-----+-----+\n");
	i = 0;
	a = cont->a.get_elems(cont->a);
	b = cont->b.get_elems(cont->b);
	size_a = cont->a.get_size(&cont->a);
	size_b = cont->a.get_size(&cont->b);
	while (i < size_a || i < size_b)
	{
		printf("|%-3d|", i);
		if (i < size_a)
			printf("\033[38;5;5m %-3d \033[0;0;0m", b[i]);
		else
			printf("\t\033[0m|");
		if (i < size_a)
			printf("|\033[38;5;6m %-3d \033[0m|\n", b[i]);
		else
			printf("|     |\n\033[0m");
		i++;
	}
	printf("+---+-----+-----+\n");
}
