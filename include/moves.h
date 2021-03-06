#ifndef MOVES_H
# define MOVES_H

# include "push_swap.h"

typedef struct s_main_cont	t_main_cont;
typedef struct s_iterator	t_iterator;
typedef struct s_deque		t_deque;

typedef enum e_moves
{
	RA	= 'r' << 8	| 'a' << 0,
	RB	= 'r' << 8	| 'b' << 0,
	RR	= 'r' << 8	| 'r' << 0,
	RRA	= 'r' << 16	| 'r'<< 8 | 'a' << 0,
	RRB	= 'r' << 16	| 'r'<< 8 | 'b' << 0,
	RRR	= 'r' << 16	| 'r'<< 8 | 'r' << 0,
	SA	= 's' << 8	| 'a' << 0,
	SB	= 's' << 8	| 'b' << 0,
	SS	= 's' << 8	| 's' << 0,
	PA	= 'p' << 8	| 'a' << 0,
	PB	= 'p' << 8	| 'b' << 0
}	t_moves;


typedef enum e_moves_to_indices
{
	REV_SA	= 0,
	REV_SB	= 1,
	REV_SS	= 2,
	REV_RA	= 3,
	REV_RB	= 4,
	REV_RR	= 5,
	REV_RRA	= 6,
	REV_RRB	= 7,
	REV_RRR	= 8,
	REV_PA	= 9,
	REV_PB	= 10
}	t_moves_to_indices;

//MOVES
void	rotate(t_deque *stack);
void    do_ra(t_main_cont *cont, t_deque *curr_moves);
void    do_rb(t_main_cont *cont, t_deque *curr_moves);
void    do_rr(t_main_cont *cont, t_deque *curr_moves);
void	rev_rotate(t_deque *stack);
void    do_rra(t_main_cont *cont, t_deque *curr_moves);
void    do_rrb(t_main_cont *cont, t_deque *curr_moves);
void    do_rrr(t_main_cont *cont, t_deque *curr_moves);
void	swap(t_deque *stack);
void    do_sa(t_main_cont *cont, t_deque *curr_moves);
void    do_sb(t_main_cont *cont, t_deque *curr_moves);
void    do_ss(t_main_cont *cont, t_deque *curr_moves);
void	push(t_deque *stack_src, t_deque *stack_dest);
void    do_pa(t_main_cont *cont, t_deque *curr_moves);
void    do_pb(t_main_cont *cont, t_deque *curr_moves);

//	stacks info tracking
static inline void	rotate_update_iterators(t_iterator *iterator);
static inline void	rev_rotate_update_iterators(t_iterator *iterator);
static inline void	swap_update_iterator(t_iterator *iterator);
static inline void	push_update_iterators(t_main_cont *cont);

//  Moves helper functions
int		convert_move_to_index(int move);
void	undo_moves(t_main_cont *cont, t_deque *curr_moves);
void	undo_n_moves(t_main_cont *cont, t_deque *curr_moves, int n);
void	discard_moves(t_main_cont *cont, t_deque *moves_buff);

#endif 