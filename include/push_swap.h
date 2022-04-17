#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

//Includes; 
//stdlib.h	: malloc(), free(), exit()
//unistd.h	: read(), write()
//stdbool.h	: clarity for certain return values
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

//TO REMOVE
# include <stdio.h>
# include <sys/wait.h>
//END OF REMOVE

//libft for ft_putstr_fd(), ft_strlen(), ft_split()
# include "../libft/libft.h"
# include "deques.h"
# include "moves.h"
# include "iterators.h"

//DEFINES
# define _ARGC_MIN 2
# define VALID_INPUTS 1
# define MAX_MOVES_FOR_5 9

# define VECTOR_INIT_SIZE 16
# define SUCCESS 0
# define FAILURE 1

# define NB_BLOCKS 2

//DEFINES
# define MAX_MOVES_FOR_5 9

//TO REMOVE
# ifndef DEBUG
#  define DEBUG 0
# endif
# define YELLOW "\033[0;33m"
# define MAGENTA "\033[0;35m"
# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define RESET_COL "\033[0m"
//END OF REMOVE

//TYPEDEFS
typedef	struct s_stack_insert_info
{
	int	dist0;
	int	pos;
	int	revpos;
	int	val;
	int	dist0_best;
	int	pos_best;
	int	revpos_best;
	int	val_best;
}	t_stack_insert_info;

typedef	struct s_insert_info
{
	t_stack_insert_info	a_info;
	t_stack_insert_info	b_info;
	int					min_cost;
	int					curr_cost;
	int					min_delta_insert;
	int					curr_delta_insert;
}	t_insert_info;


typedef struct s_main_cont	t_main_cont;
typedef struct s_main_cont
{
	t_deque			stack_a;
	t_deque			stack_b;
	t_deque			final_moves;
	t_deque			curr_moves;
	t_deque			best_moves;
	t_iterator		head_a;
	t_iterator		head_b;
	void			(**reverse_fcts)(t_main_cont *, t_deque *);
	int				min_nb_moves;
}	t_main_cont;

//PARSING
//	parse.c
void	parse(int argc, char *argv[], t_main_cont *cont);

//	init.c
void	init(t_main_cont *cont, char **args);
void	normalize_stack_values(t_deque *stack);
void	init_reverse_moves_array(void (**array)(t_main_cont *, t_deque *));

//SORTING
//	sort.c
void	sort(t_main_cont *cont);

//  partition_stack.c
void	partition_stack_in_two(t_deque *stack, t_deque *block_ids);
void	partition_stack_cutoff(t_deque *stack, t_deque *block_ids, int cutoff);
void	partition_stack_n_blocks(t_deque *stack, t_deque *block_ids, int nb_blocks);

//  partition_leaving_vals.c
void	partition_leaving_vals_cutoff(t_deque *staying_vals, t_deque *block_ids, int cutoff);
void	partition_leaving_vals_n_blocks(t_deque *leaving_vals, t_deque *block_ids, int nb_blocks);
t_deque	*get_leaving_vals_trimmed(t_deque *leaving_vals);


//  sort_small.c
void	sort_small(t_main_cont *cont);
void	try_sort_small(t_main_cont *cont);
bool	try_swap(t_main_cont *cont);
bool	try_invert_4(t_main_cont *cont);
bool	try_solution(t_main_cont *cont, t_deque *moves_buff);
bool	check_if_best_moves(t_main_cont *cont, t_deque *moves_buff);

//	insert.c
void	insert_b(t_main_cont *cont, t_deque *moves_buff);
bool	is_new_best_moves(t_insert_info *info);
int		calc_delta_insert(t_main_cont *cont, t_insert_info *info);
void	insert_elem_b(t_main_cont *cont, t_deque *moves_buff, t_insert_info *info);

//	insert_utils.c
int		dist_in_either_direction(t_insert_info *info);
int		dist_independent_direction(t_insert_info *info);

//   calc_insert_cost.c
void	init_insert_info(t_main_cont *cont, t_insert_info *info);
int		calc_insert_cost(t_insert_info *info);
void	update_insert_info(t_main_cont *cont, t_insert_info *info);

//   insert_blocks.c
void	insert_block_set_ids(t_main_cont *cont, t_deque *block_ids_a, t_deque *block_ids_b, int curr_block_id_a);
void	insert_block_b(t_main_cont *cont, t_deque *block_ids_b, int block_id);
void	insert_block_elem_b(t_main_cont *cont, t_deque *block_ids_b, t_insert_info *info);

//   sort_utils.c
bool	is_sorted(t_deque *stack, int pos_smallest);
int		get_pos_of_val(t_deque  *stack, int val);
int		get_pos_smallest_val(t_deque *stack);
int		get_pos_biggest_val(t_deque *stack);
int		get_insert_val(t_deque *haystack, int curr_val);
void	rotate_stack_to_0(t_deque *stack, int pos);
void	rotate_to_0_in_a(t_main_cont *cont, t_deque *curr_moves, int pos);
void	rotate_to_0_in_b(t_main_cont *cont, t_deque *curr_moves, int pos);
bool	is_in_stack(t_deque *stack, int val);

// SORT BIG
void	rotate_block_split(t_main_cont *cont, t_deque *block_ids, int curr_block_id, int max_val, int min_val, int median_val);
void	insert_block_a(t_main_cont *cont, t_deque *block_ids, int curr_block_id);
void	blind_push(t_main_cont *cont, t_deque *moves_list);
void	insert_last_block(t_main_cont *cont, t_deque *moves_list);
bool	block_id_is_in_stack(t_deque *block_ids, int id);
void	sort_big(t_main_cont *cont);
t_deque	*get_ordered_vals(t_deque *stack);
bool	has_smaller_than_median(t_deque *stack, int median_val, int min_val);
bool	has_bigger_than_median(t_deque *stack, int median_val, int max_val);
int		calc_block_median(t_deque *stack, t_deque *block_ids, int curr_block_id, int *max_val, int *min_val);

//    Divide & Conquer
bool	has_many_block_ids(t_deque *block_ids);
int		max_elem_leaving(t_main_cont *cont, t_deque *leaving_vals);
void	try_cutoff_n(t_main_cont *cont, t_deque *block_ids, int n, int cutoff);
void	try_n_divisions(t_main_cont *cont, t_deque *block_ids, int n);
void	try_n_divisions_smallest(t_main_cont *cont, t_deque *block_ids, int n);
void	try_n_divisions_closest(t_main_cont *cont, t_deque *block_ids, int n);

//UTILS
void	*ft_safealloc(size_t size);

//	sort_utils.c

//  PRINT UTILS
void	print_stacks(t_main_cont *cont);
void	print_single_stack(t_deque *stack);
void	print_move(int move);
void    print_all_moves(t_deque *curr_moves);
void	print_stacks_info(t_main_cont *cont);
void	print_stack_with_block_ids(int *stack, int *block_ids, int size);
void	print_staying_vals(t_main_cont *cont, t_deque *staying_vals);

//ERROR HANDLING
void	exit_on_err(char *err_message);

//CLEANUP
void	cleanup(t_main_cont *cont);

#endif
