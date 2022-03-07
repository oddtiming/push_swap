#include <stdio.h>
#include <stdbool.h>
#include "../libft/libft.h"

int		*split_args(int *argc, char *argv[]);
void	exit_on_err(char *err_message);
# define NB_BLOCKS 4

typedef struct s_block_insert_info
{
	int	block_id_curr;
	int	spread_curr;
	int	pos_head_curr;
	int	pos_tail_curr;
	int	block_id_best;
	int	spread_best;
	int	pos_head_best;
	int	pos_tail_best;

}	t_block_insert_info;

int	get_densest_block_id(int *block_ids, int size, t_block_insert_info *info)
{
	t_iterator *iter;
	int			pos_curr;

	iter = malloc(sizeof(t_iterator));
	if (!iter)
		exit_on_err("malloc err\n");
	into->block_id_curr = block_ids[0];
	inf0->pos_head_curr = 0;
	inf0->pos_head_curr = 0;
	info->spread_curr = info->pos_head_curr;
	while (--info->pos_head_curr >= 0)
	{
		spread_curr--;
		if (size - info->pos_head_curr < size / 50) //to remove outliers
			continue ;
		if (block_ids[info->pos_head_curr] == info->block_id_curr
			break;
	}

	if (info->spread_curr < info->spread_best)
	{
		info->spread_best = info->spread_curr;
		
	}

}

void	print_stack_with_block_ids(int *stack, int *block_ids, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		printf("%3d|", stack[i]);
		i++;
	}
	printf("%3d\n", stack[i]);
	i = 0;
	while (i < size - 1)
	{
		printf("%3d|" , block_ids[i]);
		i++;
	}
	printf("%3d\n\033[0m", block_ids[i]);
	return ;
}

int	*partition_stack(int *stack, int size)
{
	int		*block_ids;
	size_t	block_length;
	size_t	i;

	block_length = size / NB_BLOCKS;
	printf("block_length == %lu\n", block_length);
	block_ids = malloc(size * sizeof(int));
	if (!block_ids)
		exit_on_err("malloc err\n");
	i = 0;
	while (i < size)
	{
		block_ids[i] = stack[i] / block_length; // 0 1 2 3
		printf("stack[i] == %d\n", stack[i]);
		printf("stack[i] / NB_BLOCKS == %lu\n", stack[i] / block_length);
		i++;
	}
	return (block_ids);
}

int	main(int argc, char *argv[])
{
	t_block_insert_info	*info;
	int					*stack;
	int					*block_ids;
	int					size;

	if (argc == 1)
		exit_on_err("received no argument");
	stack = split_args(&argc, argv);
	size = argc - 1;
	block_ids = partition_stack(stack, size);
	printf("size = %d\n", size);
	for(int i = 0; i < size; i++)
	{
		printf("block_id == %d\n", block_ids[i]);
	}
	print_stack_with_block_ids(stack, block_ids, size);

	info = malloc(sizeof(t_block_insert_info));
	if (!info)
		exit_on_err("malloc err\n");
	info->spread_best = INT_MAX;
	get_densest_block_id(block_ids, size, info);

	free(stack);
	stack = NULL;
	free(block_ids);
	block_ids = NULL;
	free(info);
	info = NULL;
	return (0);
}

int	*split_args(int *argc, char *argv[])
{
	char	**temp_split;
	int		*stack;
	int		i;

	if (*argc == 2)
	{
		temp_split = ft_split(argv[1], ' ');
		if (!temp_split)
			exit_on_err("malloc oopsie unlucky fucky :((( \n");
		*argc -= 1;
		while (argv[*argc])
			*argc += 1;
		argv = temp_split;
	}
	stack = malloc((*argc) * sizeof(int));
	if (!stack)
		exit_on_err("malloc oopsie unlucky fucky :((( \n");
	i = 0;
	while (++i < *argc)
		stack[i - 1] = ft_atoi(argv[i]);
	return (stack);
}

void	exit_on_err(char *err_message)
{
	write(STDERR_FILENO, err_message, ft_strlen(err_message));
	exit (EXIT_FAILURE);
}
