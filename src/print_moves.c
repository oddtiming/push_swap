#include <stdio.h>
#include <unistd.h>

typedef enum e_list
{
        RA = 8265,
        RB = 8266,
        RRA = 828265
}       t_list;

void    print_move(int move)
{
        char    c;

        if (move >= 10000)
        {
                c = move/10000 + 32;
                write(1, &c, 1);
                move %= 10000;
        }
        if (move >= 100)
        {
                c = move/100 + 32;
                write(1, &c, 1);
                move %= 100;
        }
        c = move + 32;
        write(1, &c, 1);
        write(1, "\n", 1);
        return;
}

int     main(void)
{
        print_move(RA);
        print_move(RB);
        print_move(RRA);
        return (0);
}