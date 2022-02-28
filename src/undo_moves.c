#include "push_swap.h"

enum e_moves_to_indices
{
	REV_SA = 0,
	REV_SB = 1,
	REV_SS = 2,
	REV_RA = 3,
	REV_RB = 4,
	REV_RR = 5,
	REV_RRA = 6,
	REV_RRB = 7,
	REV_RRR = 8,
	REV_PA = 9,
	REV_PB = 10
}	t_moves_to_indices;

void	init_reverse_moves_array(void (**array)(t_main_cont *, t_deque *))
{
	array[REV_SA] = &do_sa;
	array[REV_SB] = &do_sb;
	array[REV_SS] = &do_ss;
	array[REV_RA] = &do_rra;
	array[REV_RB] = &do_rrb;
	array[REV_RR] = &do_rrr;
	array[REV_RRA] = &do_ra;
	array[REV_RRB] = &do_rb;
	array[REV_RRR] = &do_rr;
	array[REV_PA] = &do_pb;
	array[REV_PB] = &do_pa;
	return ;
}

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
	static void	(**reverse_moves_fcts)(t_main_cont *, t_deque *);
	int			move_to_index;

	if (!reverse_moves_fcts)
	{
		reverse_moves_fcts = malloc(11 * sizeof(void *));
		init_reverse_moves_array(reverse_moves_fcts);
	}
	while (moves_list->nb_elems)
	{
		move_to_index = moves_list->elems[moves_list->nb_elems - 1];
		move_to_index = convert_move_to_index(move_to_index);
		reverse_moves_fcts[move_to_index](cont, NULL);
		moves_list->remove_last(moves_list);
	}
	free (reverse_moves_fcts);
	reverse_moves_fcts = NULL;
	return ;
}
