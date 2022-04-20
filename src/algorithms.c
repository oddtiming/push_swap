#include "push_swap.h"

void	run_algorithms(t_main_cont *cont)
{
	split_in_blocks(cont);
	split_in_two(cont);
	ignore_lis(cont);

	return ;
}
