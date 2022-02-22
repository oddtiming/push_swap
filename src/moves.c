#include "push_swap.h"

void	rotate(int *stack, int size)
{
	int	temp;
	int	i;

	if (!size)
		return ;
	i = 0;
	temp = stack[0];
	while (i < size - 1)
	{
		stack[i] = stack[i + 1];
		i++;
	}
	stack[i] = temp;
	return ;
}

void	rev_rotate(int *stack, int size)
{
	int	temp;
	int	i;

	if (!size)
		return ;
	i = size - 1;	
	temp = stack[size - 1];
	while (i > 0)
	{
		stack[i] = stack[i - 1];
		i--;
	}
	stack[0] = temp;
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

void	push(int *stack_src, int *stack_dest, \
	int *size_src, int *size_dest)
{
	int	i;

	if (*size_src == 0)
		return ;
	*size_dest += 1;
	*size_src -= 1;
	i = *size_dest;
	while (--i > 0)
		stack_dest[i] = stack_dest[i - 1];
	stack_dest[0] = stack_src[0];
	i = -1;
	while (++i < *size_src)
		stack_src[i] = stack_src[i + 1];
	stack_src[i] = 0;
}

void	make_rab(int *stack, int size, int move)
{
	rotate(stack, size);
	print_move(move);
}

void	make_rrab(int *stack, int size, int move)
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
	if (move == PA)
		push(cont->B, cont->A, &cont->sizeB, &cont->sizeA);
	else if (move == PB)
		push(cont->A, cont->B, &cont->sizeA, &cont->sizeB);
	print_move(move);
}
