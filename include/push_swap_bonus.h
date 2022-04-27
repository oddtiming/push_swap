#ifndef PUSH_SWAP_BONUH_H
# define PUSH_SWAP_BONUH_H

#include "../libft/libft.h"
#include "deques.h"

typedef enum e_moves_to_indices
{
	SA_INDEX	= 0,
	SB_INDEX	= 1,
	SS_INDEX	= 2,
	RA_INDEX	= 3,
	RB_INDEX	= 4,
	RR_INDEX	= 5,
	RRA_INDEX	= 6,
	RRB_INDEX	= 7,
	RRR_INDEX	= 8,
	PA_INDEX	= 9,
	PB_INDEX	= 10
}	t_moves_to_indices;

typedef struct s_checker	t_checker;
typedef struct s_checker
{
	t_deque			stack_a;
	t_deque			stack_b;
	void			(**moves_fcts)(t_checker *);
}	t_checker;

//	checker_bonus.c
void	set_moves_pointers(void (**array)(t_checker *));
void	init_bonus(t_checker *checker, char **args);
void	do_moves(t_checker *checker);
void	free_checker(t_checker *checker);

//	parse_bonus.c
void	parse_bonus(t_checker *checker, int argc, char *argv[]);


//	moves
void	rotate(t_deque *stack);
void	checker_ra(t_checker *checker);
void	checker_rb(t_checker *checker);
void	checker_rr(t_checker *checker);
void	rev_rotate(t_deque *stack);
void	checker_rra(t_checker *checker);
void	checker_rrb(t_checker *checker);
void	checker_rrr(t_checker *checker);
void	swap(t_deque *stack);
void	checker_sa(t_checker *checker);
void	checker_sb(t_checker *checker);
void	checker_ss(t_checker *checker);
void	push(t_deque *stack_src, t_deque *stack_dest);
void	checker_pa(t_checker *checker);
void	checker_pb(t_checker *checker);


//	utils.c
void	*ft_safealloc(size_t size);

//	undo_moves.c
int		convert_move_to_index(int move);

//	errors.c
void	exit_on_err(char *err_message);

#endif