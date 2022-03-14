#ifndef DEQUES_H
# define DEQUES_H

# include "push_swap.h"

//VECTORS (need to learn how to properly link multiple headers in Makefile)
//Learned structure from https://aticleworld.com/implement-vector-in-c/
//Decided to fuck it up of my own volition, though
typedef struct s_deque t_deque;
typedef struct s_deque
{
	int		*elems;
	int		*malloced_space;
	int		size;
	int		min_elem;
	int		max_elem;
	int		capacity_total;
	int		capacity_end;
	int		capacity_front;
	bool	(*add_front)(t_deque *, int);
	bool	(*add_last)(t_deque *, int);
	void	(*free_list)(t_deque *);
	int		(*get_elem_max)(t_deque *);
	int		(*get_elem_min)(t_deque *);
	bool	(*reinit_list)(t_deque *);
	void	(*remove_front)(t_deque *);
	void	(*remove_last)(t_deque *);
	bool	(*resize_end)(t_deque *, int);
	bool	(*resize_front)(t_deque *, int);
	void	(*set_elem)(t_deque *, int, int);
}	t_deque;

//VECTORS
void 	init_deque(t_deque *deque);
void	new_deque(t_deque **deque);
bool 	deque_add_front(t_deque *deque, int new_elem);
bool 	deque_add_last(t_deque *deque, int new_elem);
void 	deque_free_list(t_deque *deque);
int		deque_get_elem_max(t_deque *deque);
int		deque_get_elem_min(t_deque *deque);
bool 	deque_reinit_list(t_deque *deque);
void	deque_remove_front(t_deque *deque);
void	deque_remove_last(t_deque *deque);
bool 	deque_resize_end(t_deque *deque, int new_size);
bool 	deque_resize_front(t_deque *deque, int new_size);
void	deque_set_elem(t_deque *deque, int pos, int new_value);

//OPERATORS
void	copy_deque(t_deque *src, t_deque *dest);
void	cat_deque(t_deque *src, t_deque *dest);
void	cat_deque_front(t_deque *src, t_deque *dest);

#endif