/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deques.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:40:21 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/05/01 20:40:39 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUES_H
# define DEQUES_H

# include <stdbool.h>
# include <stdlib.h>
# include <stddef.h>
# include <limits.h>
# include "../libft/libft.h"

# define VECTOR_INIT_SIZE 16
# define SUCCESS 0
# define FAILURE 1

//VECTORS (need to learn how to properly link multiple headers in Makefile)
//Learned structure from https://aticleworld.com/implement-vector-in-c/
//Decided to fuck it up of my own volition, though
typedef struct s_deque	t_deque;
struct s_deque
{
	int		*elems;
	int		*malloced_space;
	int		size;
	int		min_elem;
	int		max_elem;
	int		capacity_total;
	int		capacity_end;
	int		capacity_front;
	void	(*free_list)(t_deque *);
	int		(*get_elem_max)(t_deque *);
	int		(*get_elem_min)(t_deque *);
	void	(*reinit_list)(t_deque *);
	void	(*remove_front)(t_deque *);
	void	(*remove_last)(t_deque *);
	void	(*add_front)(t_deque *, int);
	void	(*add_last)(t_deque *, int);
	void	(*resize_end)(t_deque *, int);
	void	(*resize_front)(t_deque *, int);
	void	(*set_elem)(t_deque *, int, int);
};

//	deques.c
void	init_deque(t_deque *deque);
void	deque_reinit_list(t_deque *deque);

//	deque_utils.c
void	deque_resize_end(t_deque *deque, int new_size);
void	deque_resize_front(t_deque *deque, int new_size);
void	deque_free_list(t_deque *deque);
int		deque_get_elem_max(t_deque *deque);
int		deque_get_elem_min(t_deque *deque);

//	deque_modify.c
void	deque_add_front(t_deque *deque, int new_elem);
void	deque_add_last(t_deque *deque, int new_elem);
void	deque_remove_front(t_deque *deque);
void	deque_remove_last(t_deque *deque);
void	deque_set_elem(t_deque *deque, int pos, int new_value);

//	deque_operators.c
void	new_deque(t_deque **deque);
t_deque	*clone_deque(t_deque *src);
void	copy_deque(t_deque *src, t_deque *dest);
void	cat_deque(t_deque *src, t_deque *dest);
void	cat_deque_front(t_deque *src, t_deque *dest);

//ERROR HANDLING
void	exit_on_err(char *err_message);
void	ft_bzero(void *s, size_t n);

#endif