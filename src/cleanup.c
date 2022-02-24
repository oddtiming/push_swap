#include "push_swap.h"

void	cleanup(t_main_cont *cont, t_vector *moves)
{
	free (cont->malloced_space);
	moves->ptr_vec_free_list(moves);
	return ;
}
