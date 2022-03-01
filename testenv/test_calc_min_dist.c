#include <stdio.h>
#include <stdbool.h>

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
	return ((a >= 0 && b >= 0) || (a < 0) && (b < 0));
}

// This fct calculates the minimum number of moves to rotate both pos to 0.
// If both stacks have the most efficient rotations in the same sense, return.
// Else, check if most efficient to rotate indepently or in same direction.
int	calculate_abs_min_dist(int pos_a, int size_a, int pos_b, int size_b)
{
	int revpos_a;
	int dist_a;
	int revpos_b;
	int dist_b;
	int	dist_tot;

	revpos_a = pos_a - size_a;
	dist_a = pos_a;
	if (ft_abs(revpos_a) < pos_a)
		dist_a = revpos_a;
	revpos_b = pos_b - size_b;
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

int	main(void)
{
	int	size_a, size_b, pos_a, pos_b;

	size_a = 5;
	size_b = 5;
	pos_a = 1;
	pos_b = 4;
	printf("size A\t: %d\nsize B\t: %d\npos_a\t: %d\npos_b\t: %d\n", size_a, size_b, pos_a, pos_b);
	printf("dist_min==> %d\n", calculate_abs_min_dist(pos_a, size_a, pos_b, size_b));
	size_a = 88;
	size_b = 33;
	pos_a = 35;
	pos_b = 32;
	printf("size A\t: %d\nsize B\t: %d\npos_a\t: %d\npos_b\t: %d\n", size_a, size_b, pos_a, pos_b);
	printf("dist_min==> %d\n", calculate_abs_min_dist(pos_a, size_a, pos_b, size_b));
	size_a = 67;
	size_b = 33;
	pos_a = 33;
	pos_b = 31;
	printf("size A\t: %d\nsize B\t: %d\npos_a\t: %d\npos_b\t: %d\n", size_a, size_b, pos_a, pos_b);
	printf("dist_min==> %d\n", calculate_abs_min_dist(pos_a, size_a, pos_b, size_b));
	size_a = 67;
	size_b = 33;
	pos_a = 63;
	pos_b = 15;
	printf("size A\t: %d\nsize B\t: %d\npos_a\t: %d\npos_b\t: %d\n", size_a, size_b, pos_a, pos_b);
	printf("dist_min==> %d\n", calculate_abs_min_dist(pos_a, size_a, pos_b, size_b));
	size_a = 67;
	size_b = 33;
	pos_a = 2;
	pos_b = 32;
	printf("size A\t: %d\nsize B\t: %d\npos_a\t: %d\npos_b\t: %d\n", size_a, size_b, pos_a, pos_b);
	printf("dist_min==> %d\n", calculate_abs_min_dist(pos_a, size_a, pos_b, size_b));
	return (0);
}
