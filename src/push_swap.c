#include "push_swap.h"

int	main(int argc, char *argv[])
{
	t_main_cont	cont;
	
	ft_bzero(&cont, sizeof(t_main_cont));

	parse(argc, argv, &cont);
	if (DEBUG)
	{
		printf("\n----Initial Stacks----\n\n");
		print_stacks(&cont);
	}
	cont.A = normalize_stack_values(cont.A, cont.sizeA);
	if (DEBUG)
	{
		printf("\n----After normalization----\n\n");
		print_stacks(&cont);
	}
	t_vector	moves;
	if (vector_init(&moves) == FAILURE)
		exit_on_err(RED"vector failed :( \n"RESET_COL);

	sort(&cont);
	cleanup(&cont, &moves);
	return (0);
}
	// print_stacks(&cont);

	// make_move(&cont, PB);
	// make_move(&cont, PB);
	// make_move(&cont, PB);
	// make_move(&cont, PB);
	// print_stacks(&cont);

	// make_move(&cont, RRR);
	// print_stacks(&cont);
	// make_move(&cont, RR);
	// print_stacks(&cont);
	// make_move(&cont, SS);
	// print_stacks(&cont);
	// make_move(&cont, PA);
	// make_move(&cont, PA);
	// make_move(&cont, PA);
	// make_move(&cont, PA);
	// print_stacks(&cont);
	// make_move(&cont, RR);
	// print_stacks(&cont);
	// make_move(&cont, RRR);
	// print_stacks(&cont);
	// make_move(&cont, SS);
	// print_stacks(&cont);


	// rotate(cont.A, cont.sizeA, false);
	// printf("\n----After rotate----\n\n");
	// print_stacks(&cont);

	// rotate(cont.A, cont.sizeA, true);
	// rotate(cont.A, cont.sizeA, true);
	// printf("\n----After 2x reverse rotate----\n\n");
	// print_stacks(&cont);
