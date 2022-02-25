#include "push_swap.h"

void	cleanup(t_main_cont *cont)
{
	cont->a.free_list(&cont->a);
	cont->b.free_list(&cont->b);
	return ;
}
