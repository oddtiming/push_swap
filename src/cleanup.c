#include "push_swap.h"

void	cleanup(t_main_cont *cont)
{
	cont->stack_a.free_list(&cont->stack_a);
	cont->stack_b.free_list(&cont->stack_b);
	cont->moves_list.free_list(&cont->moves_list);
	return ;
}
