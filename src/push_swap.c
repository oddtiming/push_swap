#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_main_cont	*cont;

	if (argc < 2)
		exit(EXIT_FAILURE);
	cont = ft_safealloc(sizeof(t_main_cont));
	parse(argc, argv, cont);
	
	if (cont->stack_a.size <= 7)
		sort(cont);

	assign_longest_increasing_subsequence(cont);
	
	run_algorithms(cont);

	print_all_moves(&cont->best_moves);
	cleanup(cont);

	return (EXIT_SUCCESS);
}
