#include "push_swap.h"

void	print_stacks(t_stacks *stacks)
{
	int	i;

	printf("\t|\033[38;5;5m[A]\t\033[0m|\033[38;5;6m[B]\033[0m\t|\n");
	printf("+-------+-------+-------+\n");
	i = 0;
	while (i < stacks->sizeA || i < stacks->sizeB)
	{
		printf("|%d\t|", i);
		if (i < stacks->sizeA)
			printf("\033[38;5;5m[%d]\t\033[0m", stacks->A[i]);
		else
			printf("\t\033[0m|");
		if (i < stacks->sizeB)
			printf("|\033[38;5;6m[%d]\033[0m\t|\n", stacks->B[i]);
		else
			printf("|\t|\n\033[0m");
		i++;
	}
	printf("+-------+-------+-------+\n");
}

void	print_move(int move)
{
	if (move == RA)
		write(1, "ra\n", 3);
	else if (move == RB)
		write(1, "rb\n", 3);
	else if (move == RR)
		write(1, "rr\n", 3);
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
