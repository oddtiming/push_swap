#include "push_swap.h"

void	print_single_stack(t_deque *stack)
{
	int	i;

	printf("    |\033[38;5;5m [A] \033[0m|\n");
	printf("+---+-----+\n");
	i = 0;
	while (i < stack->size)
	{
		printf("|%-3d|", i);
		if (i < stack->size)
			printf("\033[38;5;5m %-3d \033[0;0;0m|\n", stack->elems[i]);
		else
			printf("\t\033[0m|\n");
		i++;
	}
	printf("+---+-----+\n");
}


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
	size_a = cont->stack_a.size;
	size_b = cont->stack_b.size;
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
	printf("\tmax elem in a = %d\n", cont->stack_a.max_elem);
	printf("\tmin elem in a = %d\n", cont->stack_a.min_elem);
	printf("\tpos: %d\n", cont->head_a.index);
	printf("\tsize of stack_a = %d\n", cont->stack_a.size);

	printf(YELLOW"**stack_b**\n");
	printf("\tmax elem in b = %d\n", cont->stack_b.max_elem);
	printf("\tmin elem in b = %d\n", cont->stack_b.min_elem);
	printf("\tpos: %d\n", cont->head_b.index);
	printf("\tsize of stack_b = %d\n"RESET_COL, cont->stack_b.size);

	printf(CYAN"\t==> CURR TOTAL: %d \n"RESET_COL, cont->curr_moves.size);
	print_all_moves(&cont->curr_moves);
	printf(BLUE"\t==> BEST TOTAL: %d \n"RESET_COL, cont->best_moves.size);
	print_all_moves(&cont->best_moves);
	printf(MAGENTA"\t==> FINAL TOTAL: %d \n"RESET_COL, cont->final_moves.size);
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
    while (i < curr_moves->size)
    {
        print_move(curr_moves->elems[i]);
        i++;
    }
	if (DEBUG)
	{
		if (!i)
			printf(RESET_COL"\t====== No move stored ======\n");
		else
			printf(GREEN"\t====== Total nb_moves == %d ======\n"RESET_COL, i);
	}
    return ;
}
