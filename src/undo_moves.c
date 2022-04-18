#include "push_swap.h"

/* 
 * REV_SA  = 0 	| (a => 0) + 3 * (s => 0)	== 0 + 3*0 == 0 | rev_fcts[0] ==> &do_sa
 * REV_SB  = 1 	| (b => 1) + 3 * (s => 0)	== 1 + 3*0 == 1 | rev_fcts[1] ==> &do_sb
 * REV_SS  = 2 	| (r/s => 2) + 3 * (s => 0)	== 2 + 3*0 == 2 | rev_fcts[5] ==> &do_ss
 * REV_RA  = 3 	|	{...}
 * REV_RB  = 4 	|
 * REV_RR  = 5 	| (r/s => 2) + 3 * (r => 1)	== 2 + 3*1 == 5 | rev_fcts[5] ==> &do_rrr
 * REV_RRA = 6	|	{...}
 * REV_RRB = 7	| (b => 1) + 3 * (rr => q => 2) == 1 + 3*2 == 7| rev_fcts[7] ==> &do_rb
 * REV_RRR = 8	|	{...}
 * REV_PA  = 9 	|
 * REV_PB  = 10	| (b => 1) + 3 * (p => 3)	== 1 + 3*3 == 10 | rev_fcts[10] ==> &do_pa
 */

//Could just be:
//	return ((((move & 0xFF)) / 10  - 88) + (-3 * ((move >> 8) & 0xFF) - 73));
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

void	undo_moves(t_main_cont *cont, t_deque *curr_moves)
{
	int			move_to_index;

	move_to_index = 0;
	while (curr_moves->size)
	{
		move_to_index = curr_moves->elems[curr_moves->size - 1];
		move_to_index = convert_move_to_index(move_to_index);
		cont->reverse_fcts[move_to_index](cont, NULL);
		curr_moves->remove_last(curr_moves);
	}
	return ;
}

void	undo_n_moves(t_main_cont *cont, t_deque *curr_moves, int n)
{
	int			move_to_index;

	if (n <= 0)
		return ;
	move_to_index = 0;
	while (n-- && curr_moves->size)
	{
		move_to_index = curr_moves->elems[curr_moves->size - 1];
		move_to_index = convert_move_to_index(move_to_index);
		cont->reverse_fcts[move_to_index](cont, NULL);
		curr_moves->remove_last(curr_moves);
	}
	return ;
}

void	discard_moves(t_main_cont *cont, t_deque *moves_buff)
{
	if (!moves_buff)
		return ;
	undo_moves(cont, moves_buff);
	moves_buff->free_list(moves_buff);
	free(moves_buff);
	return ;
}
