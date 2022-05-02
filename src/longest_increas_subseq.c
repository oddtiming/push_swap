/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cherrypick.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iyahoui- <iyahoui-@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 21:40:44 by iyahoui-          #+#    #+#             */
/*   Updated: 2022/04/27 23:38:58 by iyahoui-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	longest_increasing_subsequence(t_deque **list, t_deque *stack)
{
	int		list_size;
	int		i;
	int		j;

	i = 0;
	list_size = 1;
	while (++i < stack->size)
	{
		if (stack->elems[i] > list[list_size - 1]->max_elem)
		{
			list[list_size] = clone_deque(list[list_size - 1]);
			list[list_size]->add_last(list[list_size], stack->elems[i]);
			list_size++;
		}
		else
		{
			j = list_size - 1;
			while (list[j]->max_elem > stack->elems[i] && j >= 0)
				j--;
			copy_deque(list[j], list[j + 1]);
			list[j + 1]->add_last(list[j + 1], stack->elems[i]);
		}
	}
	return (list_size);
}

t_deque	*get_ordered_vals(t_deque *stack)
{
	t_deque	**list;
	t_deque	*staying_vals;
	int		list_size;

	list = ft_xalloc(stack->max_elem * sizeof(t_deque *));
	new_deque(&list[0]);
	list[0]->add_last(list[0], stack->elems[0]);
	list_size = longest_increasing_subsequence(list, stack);
	staying_vals = list[list_size - 1];
	free_deque_list(list, list_size - 1);
	return (staying_vals);
}

static void	normalize_staying_vals(t_main_cont *cont)
{
	int	i;

	i = 0;
	while (i < cont->staying_vals.size)
	{
		if (cont->staying_vals.elems[0] > cont->stack_a.max_elem)
			cont->staying_vals.add_last(
				&cont->staying_vals,
				cont->staying_vals.elems[0] - cont->stack_a.size - 1);
		else
			cont->staying_vals.add_last(
				&cont->staying_vals,
				cont->staying_vals.elems[0]);
		cont->staying_vals.remove_front(&cont->staying_vals);
		i++;
	}
}

static void	assign_leaving_vals(t_main_cont *cont)
{
	int	i;

	i = 0;
	while (i < cont->stack_a.size)
	{
		if (is_in_stack(&cont->staying_vals, cont->stack_a.elems[i]))
			cont->leaving_vals.add_last(&cont->leaving_vals, -1);
		else
			cont->leaving_vals.add_last(
				&cont->leaving_vals,
				cont->stack_a.elems[i]);
		i++;
	}
}

void	assign_longest_increasing_subsequence(t_main_cont *cont)
{
	t_deque		*curr_staying_vals;
	t_deque		*staying_stack;
	int			i;

	staying_stack = clone_deque(&cont->stack_a);
	i = 0;
	while (i < cont->stack_a.size)
	{
		rotate_stack_to_0(staying_stack, get_pos_of_val(staying_stack, i));
		curr_staying_vals = get_ordered_vals(staying_stack);
		if (curr_staying_vals->size > cont->staying_vals.size)
			copy_deque(curr_staying_vals, &cont->staying_vals);
		staying_stack->remove_front(staying_stack);
		staying_stack->add_front(staying_stack, staying_stack->size + i + 1);
		curr_staying_vals->free_list(curr_staying_vals);
		free (curr_staying_vals);
		i++;
	}
	normalize_staying_vals(cont);
	staying_stack->free_list(staying_stack);
	free(staying_stack);
	assign_leaving_vals(cont);
	return ;
}
