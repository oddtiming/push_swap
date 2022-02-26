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
    int nb_moves;

    i = 0;
    nb_moves = moves_list->get_size(moves_list);
    while (i < nb_moves)
    {
        print_move(moves_list->get_elem(moves_list, i));
        i++;
    }
    return ;
}
