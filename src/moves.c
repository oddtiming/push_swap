#include "push_swap.h"

//Look what you've done to me, Norminette...
void	rotate(int *stack, int size, bool is_reverse)
{
	int	temp;
	int i;

	temp = is_reverse * stack[size - 1] + !is_reverse * stack[0];
	i = is_reverse * size + !is_reverse * (-1);
	if (is_reverse == true)
		while (--i > 0)
			stack[i] = stack[i - 1];
	else
		while (++i < size - 1)
			stack[i] = stack[i + 1];
	stack[i] = temp;
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

void	push(int *stack_src, int *stack_dest, int *size_src, int *size_dest)
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

void	make_move(t_stacks *stacks, int move)
{
	if (!(move >= RA && move <= PB))
		exit_on_err("make_move received wrong input\n");
	if (move == RA || move == RR)
		rotate(stacks->A , stacks->sizeA , false);
	if (move == RB || move == RR)
		rotate(stacks->B , stacks->sizeB , false);
	else if (move == RRA || move == RRR)
		rotate(stacks->A , stacks->sizeA , true);
	if (move == RRB || move == RRR)
		rotate(stacks->B , stacks->sizeB , true);
	else if (move == SA || move == SS)
		swap(stacks->A, stacks->sizeA);
	if (move == SB || move == SS)
		swap(stacks->B, stacks->sizeB);
	else if (move == PA)
		push(stacks->B, stacks->A, &stacks->sizeB, &stacks->sizeA);
	else if (move == PB)
		push(stacks->A, stacks->B, &stacks->sizeA, &stacks->sizeB);
	print_move(move);
}
