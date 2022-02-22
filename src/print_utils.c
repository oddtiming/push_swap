#include "push_swap.h"

void	print_single_stack(int *stack, int size)
{
	int	i;

	printf("    |\033[38;5;5m [A] \033[0m|\n");
	printf("+---+-----+\n");
	i = 0;
	while (i < size)
	{
		printf("|%-3d|", i);
		if (i < size)
			printf("\033[38;5;5m %-3d \033[0;0;0m|\n", stack[i]);
		else
			printf("\t\033[0m|\n");
		i++;
	}
	printf("+---+-----+\n");
}

void	print_stacks(t_main_container *cont)
{
	int	i;

	printf("    |\033[38;5;5m [A] \033[0m|\033[38;5;6m [B] \033[0;0;0m|\n");
	printf("+---+-----+-----+\n");
	i = 0;
	while (i < cont->sizeA || i < cont->sizeB)
	{
		printf("|%-3d|", i);
		if (i < cont->sizeA)
			printf("\033[38;5;5m %-3d \033[0;0;0m", cont->A[i]);
		else
			printf("\t\033[0m|");
		if (i < cont->sizeB)
			printf("|\033[38;5;6m %-3d \033[0m|\n", cont->B[i]);
		else
			printf("|     |\n\033[0m");
		i++;
	}
	printf("+---+-----+-----+\n");
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
