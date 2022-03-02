#include "push_swap.h"

void	print_stacks(t_main_cont *cont)
{
	int	*stack_a;
	int	*stack_b;
	int	size_a;
	int	size_b;
	int	i;

	printf("    |\033[38;5;5m [A] \033[0m|\033[38;5;6m [B] \033[0;0;0m|\n");
	printf("+---+-----+-----+\n");
	i = 0;
	stack_a = cont->stack_a.elems;
	stack_b = cont->stack_b.elems;
	size_a = cont->stack_a.nb_elems;
	size_b = cont->stack_b.nb_elems;
	while (i < size_a || i < size_b)
	{
		printf("|%-3d|", i);
		if (i < size_a)
			printf("\033[38;5;5m %-3d \033[0;0;0m", stack_a[i]);
		else
			printf("     \033[0m");
		if (i < size_b)
			printf("|\033[38;5;6m %-3d \033[0m|\n", stack_b[i]);
		else
			printf("|     |\n\033[0m");
		i++;
	}
	printf("+---+-----+-----+\n");
}

void	print_stacks_info(t_main_cont *cont)
{
	print_stacks(cont);

	printf(YELLOW"**stack_a**\n");
	printf("\tmax elem in a = %d\n", cont->stack_a.elem_max);
	printf("\tpos: %d\n", cont->tail_a.index);
	printf("\tmin elem in a = %d\n", cont->stack_a.elem_min);
	printf("\tpos: %d\n", cont->head_a.index);
	printf("\tsize of stack_a = %d\n", cont->stack_a.nb_elems);

	printf(YELLOW"**stack_b**\n");
	printf("\tmax elem in b = %d\n", cont->stack_b.elem_max);
	printf("\tpos: %d\n", cont->tail_b.index);
	printf("\tmin elem in b = %d\n", cont->stack_b.elem_min);
	printf("\tpos: %d\n", cont->head_b.index);
	printf("\tsize of stack_b = %d\n"RESET_COL, cont->stack_b.nb_elems);

	printf(CYAN"\t==> TEMP TOTAL: %d \n"RESET_COL, cont->curr_moves.nb_elems);
	print_all_moves(&cont->curr_moves);
	printf(CYAN"\t==> BEST TOTAL: %d \n"RESET_COL, cont->final_moves.nb_elems);
	print_all_moves(&cont->final_moves);

	return ;
}

void    print_move(int move)
{
    char    c;

    if (move >> 16 & 0xFF)
    {
        c = (char)(move >> 16 & 0xFF);
        write(1, &c, 1);
    }
    c = (char)(move >> 8 & 0xFF);
    write(1, &c, 1);
    c = (char)(move & 0xFF);
    write(1, &c, 1);
    write(1, "\n", 1);
    return;
}

void    print_all_moves(t_deque *curr_moves)
{
    int i;

    i = 0;
    while (i < curr_moves->nb_elems)
    {
        print_move(curr_moves->elems[i]);
        i++;
    }
	if (DEBUG)
	{
		if (!i)
			printf(RED"\n\t====== No move stored ======\n"RESET_COL);
		else
			printf(GREEN"\n\t====== Total nb_moves == %d ======\n"RESET_COL, i);
	}
    return ;
}
