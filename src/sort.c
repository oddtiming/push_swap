#include "push_swap.h"

bool	try_swap(t_main_cont *cont)
{
	t_iterator	iterator;

	set_iterator(&iterator, 0, cont->stack_a.nb_elems, 0);
	while (iterate_n_loops(&iterator, 1))
	{
		rotate_pos_in_a_to_0(cont, &cont->moves_list, iterator.index);
		do_sa(cont, &cont->moves_list);
		if (is_sorted(&cont->stack_a, cont->pos_min_val_a.index))
		{
			rotate_pos_in_a_to_0(cont, &cont->moves_list, cont->pos_min_val_a.index);
			return (true);
		}
		undo_moves(cont, &cont->moves_list);
	}
	return (false);
}

static int ft_max(int a, int b)
{
	return ((a >= b) * a + (b > a) * b);
}

static int ft_min(int a, int b)
{
	return ((a <= b) * a + (b < a) * b);
}

static int ft_abs(int a)
{
	return ((a >= 0) * a + (a < 0) * (-a));
}

static bool	ft_same_sign(int a, int b)
{
	return ((a >= 0 && b >= 0) || ((a < 0) && (b < 0)));
}

// This fct calculates the minimum number of moves to rotate both pos to 0.
// If both stacks have the most efficient rotations in the same sense, return.
// Else, check if most efficient to rotate indepently or in same direction.
int	calculate_abs_min_dist(t_main_cont *cont, int pos_a, int pos_b)
{
	int revpos_a;
	int dist_a;
	int revpos_b;
	int dist_b;
	int	dist_tot;

	if (pos_a < 0 || pos_b << 0)
		return (INT_MAX);
	revpos_a = pos_a - cont->stack_a.nb_elems;
	dist_a = pos_a;
	if (ft_abs(revpos_a) < pos_a)
		dist_a = revpos_a;
	revpos_b = pos_b - cont->stack_b.nb_elems;
	dist_b = pos_b;
	if (ft_abs(revpos_b) < pos_b)
		dist_b = revpos_b;
	dist_tot = ft_max(ft_abs(dist_a), ft_abs(dist_b));
	if (ft_same_sign(dist_a, dist_b))
		return (dist_tot);
	else
		dist_tot = ft_min(ft_max(pos_a, pos_b), ft_max(-revpos_a, -revpos_b));
	dist_tot = ft_min(dist_tot, ft_abs(dist_a) + ft_abs(dist_b));
	return (dist_tot);
}

void	insert_elem_b(t_main_cont *cont, int pos_a, int pos_b)
{
	int revpos_a;
	int dist_a;
	int revpos_b;
	int dist_b;
	int	dist_tot;

	revpos_a = pos_a - cont->stack_a.nb_elems;
	dist_a = pos_a;
	if (ft_abs(revpos_a) < pos_a)
		dist_a = revpos_a;
	revpos_b = pos_b - cont->stack_b.nb_elems;
	dist_b = pos_b;
	if (ft_abs(revpos_b) < pos_b)
		dist_b = revpos_b;
	dist_tot = ft_max(ft_abs(dist_a), ft_abs(dist_b));
	// case for they both need to go in the same sense
	if (ft_same_sign(dist_a, dist_b))
	{
		if (dist_a > 0)
		{
			while (dist_tot--)
			{
				dist_a--;
				dist_b--;
				if (dist_a < 0)
					do_rb(cont, &cont->moves_list);
				else if (dist_b < 0)
					do_ra(cont, &cont->moves_list);
				else
					do_rr(cont, &cont->moves_list);
			}
			do_pa(cont, &cont->moves_list);
		}
		else
		{
			while (dist_tot--)
			{
				dist_a++;
				dist_b++;
				if (dist_a > 0)
					do_rrb(cont, &cont->moves_list);
				else if (dist_b > 0)
					do_rra(cont, &cont->moves_list);
				else
					do_rrr(cont, &cont->moves_list);
			}
			do_pa(cont, &cont->moves_list);
		}
		return ;
	}
	// case where their respective best rotations are in opposite directions,
	// but it's still better to move them in same direction
	else if (ft_min(ft_max(pos_a, pos_b), ft_max(-revpos_a, -revpos_b)) < ft_abs(dist_a) + ft_abs(dist_b) )
	{
		if (ft_max(pos_a, pos_b) < ft_max(-revpos_a, -revpos_b))
		{
			while (dist_tot--)
			{
				dist_a--;
				dist_b--;
				if (dist_a < 0)
					do_rb(cont, &cont->moves_list);
				else if (dist_b < 0)
					do_ra(cont, &cont->moves_list);
				else
					do_rr(cont, &cont->moves_list);
			}
			do_pa(cont, &cont->moves_list);
		}
		else
		{
			while (dist_tot--)
			{
				dist_a++;
				dist_b++;
				if (dist_a > 0)
					do_rrb(cont, &cont->moves_list);
				else if (dist_b > 0)
					do_rra(cont, &cont->moves_list);
				else
					do_rrr(cont, &cont->moves_list);
			}
			do_pa(cont, &cont->moves_list);
		}
		return ;
	}
	// case where they each do their own thing. that's okay too.
	else
	{
		if (dist_a >= 0)
			while (dist_a--)
				do_ra(cont, &cont->moves_list);
		else
			while (dist_a++)
				do_rra(cont, &cont->moves_list);
		if (dist_b >= 0)
			while (dist_b--)
				do_rb(cont, &cont->moves_list);
		else
			while (dist_b++)
				do_rrb(cont, &cont->moves_list);
	}
	return ;	
}

//Here's the logic for insert_b:
//	Should be recursive and take a moves_list as a parameter;
//	for each iteration, the fct should:
//		- keep in store the positions for the N smallest nb_moves to insert
//		- Iterate through these N values to compare the outcomes recursively can be.
//		- undo the last_move if the 
//	at the end, the list with the smallest nb_moves is concatenated to cont's moves_list
//
// FOR NOW, though, simply calculate which element is fastest to insert, mb recursively
void	insert_b(t_main_cont *cont)
{
	int	best_pos_in_a;
	int	best_pos_in_b;
	int	curr_pos_in_b;
	int	curr_pos_in_a;
	int	curr_insert_value_in_a;
	int	curr_cost;
	int	min_cost;
	
	min_cost = INT_MAX;
	curr_pos_in_b = 0;
	best_pos_in_a = 0;
	best_pos_in_b = 0;
	while (curr_pos_in_b < cont->stack_b.nb_elems)
	{
		curr_insert_value_in_a = get_next_bigger(&cont->stack_a, cont->stack_b.elems[curr_pos_in_b]);
		//Will calculate the minimum distance between two points in two stacks
		curr_pos_in_a = get_pos_of_val(&cont->stack_a, curr_insert_value_in_a);
		curr_cost = calculate_abs_min_dist(cont, curr_pos_in_a, curr_pos_in_b);
		if (curr_cost < min_cost)
		{
			min_cost = curr_cost;
			best_pos_in_b = curr_pos_in_b;
			best_pos_in_a = curr_pos_in_a;
		}
		curr_pos_in_b++;
	}
	if (DEBUG)
	{
		printf(YELLOW"insert_b found best elem to be stack_b[%d] == %d\n"RESET_COL, best_pos_in_b, cont->stack_b.elems[best_pos_in_b]);
		printf(YELLOW"corresponding insert value was stack_a[%d] == %d\n"RESET_COL, best_pos_in_a, cont->stack_a.elems[best_pos_in_a]);
	}
	insert_elem_b(cont, best_pos_in_a, best_pos_in_b);
	if (cont->stack_b.nb_elems)
		insert_b(cont);
}

void	sort_small(t_main_cont *cont)
{
	// t_deque	*temp;

	if (is_sorted(&cont->stack_a, cont->pos_min_val_a.index))
	{
		rotate_pos_in_a_to_0(cont, &cont->moves_list, cont->pos_min_val_a.index);
		return ;
	}
	else if (try_swap(cont))
		return ;
	// if (cont->stack_b.nb_elems > 0)
	// 	insert_b(cont);
	
	// else
	// {
	// 	try_pb(cont, smallest_moves_list);
	// 	smallest_nb_moves = smallest_moves_list.nb_elems;
	// 	try_invert4(cont, temp);
	// 	if (temp.nb_elems > smallest_nb_moves)
	// 	{
	// 		smallest_moves_list->free_list(smallest_moves_list);
	// 		smallest_moves_list = temp;
	// 	}
	// }
	return ;
}

void	sort(t_main_cont *cont)
{
	if (cont->stack_a.nb_elems < 10)
		sort_small(cont);
	return ;
}