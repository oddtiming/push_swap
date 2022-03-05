#include <stdio.h>
#include <stdbool.h>

int ft_max(int a, int b)
{
	return ((a >= b) * a + (b > a) * b);
}

int ft_min(int a, int b)
{
	return ((a <= b) * a + (b < a) * b);
}

int ft_abs(int a)
{
	return ((a >= 0) * a + (a < 0) * (-a));
}

bool	ft_same_sign(int a, int b)
{
	return ((a >= 0 && b >= 0) || ((a < 0) && (b < 0)));
}

void	set_next_pos(int *pos, int size)
{
	if (*pos == size - 1)
		*pos = 0;
	else
		*pos += 1;
}

int	get_next_pos(int pos, int size)
{
	if (pos == size - 1)
		return (0);
	return (pos + 1);
}


int	calc_delta_two_values(int val_a, int max_a, int min_a, int val_b, int max_b, int min_b)
{
	int	delta_insert;

	delta_insert = ft_abs(val_a - val_b); // is now equal to the diff between the two
	//if smaller than half the absolute diff
	if (delta_insert <= (ft_max(max_a, max_b) + 1) / 2)
		return (delta_insert);
	delta_insert = (max_a - val_a) + (val_b - min_b) + 1;
	if (val_b > val_a)
		delta_insert = (max_b - val_b) + (val_a - min_a) + 1;
	return (delta_insert);
}

void	print_test(int val_a, int max_a, int min_a, int val_b, int max_b, int min_b)
{
	int	delta_values;

	delta_values = calc_delta_two_values(val_a, max_a, min_a, val_b, max_b, min_b);
	printf("for val_a = %d \n \
			max_a = %d \n \
			min_a = %d \n \
			val_b = %d \n \
			max_b = %d \n \
			min_b = %d \n", val_a, max_a, min_a, val_b, max_b, min_b);
	printf("delta_values = %d \n\n", delta_values);
	return ;
}

int	main(void)
{
	int	val_a = 0; 
	int	max_a = 7;
	int	min_a = 0; 
	int	val_b = 4; 
	int	max_b = 8; 
	int	min_b = 2;
	print_test(val_a, max_a, min_a, val_b, max_b, min_b);

	val_a = 0; 
	max_a = 7;
	min_a = 0; 
	val_b = 5; 
	max_b = 8; 
	min_b = 2;
	print_test(val_a, max_a, min_a, val_b, max_b, min_b);

	val_a = 0; 
	max_a = 7;
	min_a = 0; 
	val_b = 5; 
	max_b = 9; 
	min_b = 2;
	print_test(val_a, max_a, min_a, val_b, max_b, min_b);

	val_a = 0; 
	max_a = 7;
	min_a = 0; 
	val_b = 4; 
	max_b = 9; 
	min_b = 2;
	print_test(val_a, max_a, min_a, val_b, max_b, min_b);
	return (0);
}