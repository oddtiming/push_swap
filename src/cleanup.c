#include "push_swap.h"

void	cleanup(t_main_container *cont)
{
	if (DEBUG)
		printf(RED"**entered cleanup**\n"RESET_COL);
	free (cont->malloced_space);
	return ;
}
