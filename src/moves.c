#include "push_swap.h"

typedef enum s_moves
{
	RA = 1,
	RB = 2,
	RR = 3,
	RRA = 4,
	RRB = 5,
	RRR = 6,
	SA = 7,
	SB = 8,
	SS = 9,
	PA = 10,
	PB = 11
}	t_moves;

//Look what you've done to me, Norminette...
inline void	rotate(int *stack, int size, bool is_reverse)
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

inline void	swap(int *stack, int size)
{
	int	temp;

	if (size <= 1)
		return ;
	temp = stack[0];
	stack[0] = stack[1];
	stack[1] = temp;
}
