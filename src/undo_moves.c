#include "push_swap.h"

/* 
 * REV_SA  = 0 	|	(a => 0) + 3 * (s => 0)	==> 0 	| rev_fcts[0] ==> &do_sa
 * REV_SB  = 1 	|	(b => 1) + 3 * (s => 0)	==> 1 	| rev_fcts[1] ==> &do_sb
 * REV_SS  = 2 	|
 * REV_RA  = 3 	|	{...}
 * REV_RB  = 4 	|
 * REV_RR  = 5 	|	(r => 2) + 3 * (r => 1)	==> 5 	| rev_fcts[5] ==> &do_rrr
 * REV_RRA = 6	|	{...}
 * REV_RRB = 7	|	(b => 1) + 3 * (rr => q -> 2) ==> 7| rev_fcts[7] ==> &do_rb
 * REV_RRR = 8	|	{...}
 * REV_PA  = 9 	|
 * REV_PB  = 10	|	(b => 1) + 3 * (p => 3)	==> 10	| rev_fcts[10] ==> &do_pa
 */
int	convert_move_to_index(int move)
{
	int	move_to_index;

	//transform {'a', 'b', 's' || 'r'} => {0, 1, 2};
	move_to_index = ((move & 0xFF) - 'a' + 9) / 10;

	//if move starts with 'rr', convert it to 'q' instead
	if (move >> 16 == 'r')
		move = (move & 0xFF) | (('r' - 1) << 8);
	//transform {'p', 'q', 'r', 's'} => {3, 2, 1, 0};
	//p is the only family of fcts with less than 3 members, needs to be last.
	//get the position and multiply by 3 to get the offset.
	move_to_index += (((move >> 8) & 0xFF) - 'p' - 3) * (-1) * 3;
	
	return (move_to_index);
}

void	undo_moves(t_main_cont *cont, t_deque *moves_list)
{
	int			move_to_index;

	while (moves_list->nb_elems)
	{
		move_to_index = moves_list->elems[moves_list->nb_elems - 1];
		move_to_index = convert_move_to_index(move_to_index);
		cont->reverse_fcts[move_to_index](cont, NULL);
		moves_list->remove_last(moves_list);
	}
	return ;
}
