#include "push_swap.h"

void	cleanup(t_main_container *cont)
{
	free (cont->malloced_space);
	return ;
}
