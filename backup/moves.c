#include "push_swap.h"

void	rotate(int **stack, int size)
{
	*(*stack + size) = *stack[0];
	*stack[0] = 0;
	*stack += 1;
	return ;
}

void	rev_rotate(int **stack, int size)
{
	*(*stack - 1) = *(*stack + size - 1);
	*(*stack + size) = 0;
	*stack -= 1;
	return ;
}

void	swap(int *stack, int size)
{
	int	temp;

	if (size <= 1)
		return ;
	temp = stack[0];
	stack[0] = stack[1];
	stack[1] = temp;
}

static void	private_push(int **stack_src, int **stack_dest, \
							int *size_src, int *size_dest)
{
	*(*stack_dest - 1) = *stack_src[0];
	*stack_src[0] = 0;
	*size_dest += 1;
	*size_src -= 1;
	*stack_dest -= 1;
	*stack_src += 1;
}

void	push(t_main_cont *cont, int move)
{
	if (move == PA)
		private_push(&cont->B, &cont->A, &cont->sizeB, &cont->sizeA);
	else if (move == PB)
		private_push(&cont->A, &cont->B, &cont->sizeA, &cont->sizeB);
}
