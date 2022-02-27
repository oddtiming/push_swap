#include "push_swap.h"

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

void    print_all_moves(t_vector *moves_list)
{
    int i;

    i = 0;
    while (i < moves_list->list.nb_elems)
    {
        print_move(moves_list->list.elems[i]);
        i++;
    }
    return ;
}
