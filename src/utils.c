#include "push_swap.h"

void	print_stacks(t_stacks *stacks)
{
	int	i;

	printf("\t\033[38;5;5m[A]\t\033[38;5;6m[B]\n\033[0m");
	printf("------------------------\n");
	i = 0;
	while (i < stacks->size)
	{
		if (!stacks->A[i] && !stacks->B[i])
			return ;
		printf("%d\t", i);
		if (stacks->A[i])
			printf("\033[38;5;5m[%d]\t\033[0m", stacks->A[i]);
		else
			printf("\t\033[0m");
		if (stacks->B[i])
			printf("\033[38;5;6m[%d]\n\033[0m", stacks->B[i]);
		else
			printf("\n\033[0m");
		i++;
	}

}

void	print_move(int move)
{
	if (move == RA)
		write(1, "ra\n", 3);
	else if (move == RB)
		write(1, "rb\n", 3);
	else if (move == RR)
		write(1, "rb\n", 3);
	else if (move == RRA)
		write(1, "rra\n", 4);
	else if (move == RRB)
		write(1, "rrb\n", 4);
	else if (move == RRR)
		write(1, "rrr\n", 4);
	else if (move == SA)
		write(1, "sa\n", 3);
	else if (move == SB)
		write(1, "sb\n", 3);
	else if (move == SS)
		write(1, "ss\n", 3);
	else if (move == PA)
		write(1, "pa\n", 3);
	else if (move == PB)
		write(1, "pb\n", 3);
}
