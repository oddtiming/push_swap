#include "push_swap.h"

void	make_rab(int **stack, int size, int move)
{
	rotate(stack, size);
	print_move(move);
}

void	make_rrab(int **stack, int size, int move)
{
	rev_rotate(stack, size);
	print_move(move);
}

void	make_sab(int *stack, int size, int move)
{
	swap(stack, size);
	print_move(move);
}

void	make_push(t_main_container *cont, int move)
{
	push(cont, move);
	print_move(move);
}
