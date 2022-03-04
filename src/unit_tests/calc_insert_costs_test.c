#include "../../include/push_swap.h"

typedef	struct s_test_insert_info
{
	t_stack_insert_info	a_info;
	t_stack_insert_info	b_info;
	int					min_cost;
	int					curr_cost;
	int					min_delta_insert;
	int					curr_delta_insert;
}	t_test_insert_info;

int	test_test_calc_insert_cost(void)
{
	int	size_a, size_b, pos_a, pos_b;

	size_a = 5;
	size_b = 5;
	pos_a = 1;
	pos_b = 4;
	printf("size A\t: %d\nsize B\t: %d\npos_a\t: %d\npos_b\t: %d\n", size_a, size_b, pos_a, pos_b);
	printf("dist_min==> %d\n", test_calc_insert_cost(pos_a, size_a, pos_b, size_b));
	size_a = 88;
	size_b = 33;
	pos_a = 35;
	pos_b = 32;
	printf("size A\t: %d\nsize B\t: %d\npos_a\t: %d\npos_b\t: %d\n", size_a, size_b, pos_a, pos_b);
	printf("dist_min==> %d\n", test_calc_insert_cost(pos_a, size_a, pos_b, size_b));
	size_a = 67;
	size_b = 33;
	pos_a = 33;
	pos_b = 31;
	printf("size A\t: %d\nsize B\t: %d\npos_a\t: %d\npos_b\t: %d\n", size_a, size_b, pos_a, pos_b);
	printf("dist_min==> %d\n", test_calc_insert_cost(pos_a, size_a, pos_b, size_b));
	size_a = 67;
	size_b = 33;
	pos_a = 63;
	pos_b = 15;
	printf("size A\t: %d\nsize B\t: %d\npos_a\t: %d\npos_b\t: %d\n", size_a, size_b, pos_a, pos_b);
	printf("dist_min==> %d\n", test_calc_insert_cost(pos_a, size_a, pos_b, size_b));
	size_a = 67;
	size_b = 33;
	pos_a = 2;
	pos_b = 32;
	printf("size A\t: %d\nsize B\t: %d\npos_a\t: %d\npos_b\t: %d\n", size_a, size_b, pos_a, pos_b);
	printf("dist_min==> %d\n", test_calc_insert_cost(pos_a, size_a, pos_b, size_b));
	return (0);
}
