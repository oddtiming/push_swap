#include "push_swap.h"

void	cleanup(t_main_cont *cont)
{
	cont->stack_a.free_list(&cont->stack_a);
	cont->stack_b.free_list(&cont->stack_b);
	cont->final_moves.free_list(&cont->final_moves);
	cont->curr_moves.free_list(&cont->curr_moves);
	cont->best_moves.free_list(&cont->best_moves);
	free (cont->reverse_fcts);
	free (cont);
	return ;
}
