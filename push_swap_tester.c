#include "./incl/push_swap.h"
#include <fcntl.h>
#include <errno.h>

typedef struct	s_cmd {
	int		in_fd;
	int		out_fd;
	pid_t	pid;
}	t_cmd;

void	assign_cmd_fds(t_cmd *ps, t_cmd *checker, t_cmd *wc, int log_fd);
void 	execute_permutation(char *stack);
void	exec_ps(t_cmd ps, char *stack);
void	exec_checker(t_cmd ps, char *stack);
void	exec_wc(t_cmd ps, int log_fd);
void	tester_cleanup(t_cmd *ps, t_cmd *checker, t_cmd *wc, int log_fd);

int	main(void)
{
	char	*curr_line;
	int		fd;

	fd = open("./5_permutations.txt", O_RDONLY);
	curr_line = get_next_line(fd);
	while (curr_line && ft_isdigit(curr_line[0]))
	{
		//Remove the '\n'
		curr_line[ft_strlen(curr_line) - 1] = 0;
		printf(MAGENTA"---> curr_line = '%s'\n"RESET_COL, curr_line);
		//Go to execute
		execute_permutation(curr_line);
		free (curr_line);
		curr_line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void	execute_permutation(char *stack)
{
	static t_cmd	ps;
	static t_cmd	checker;
	static t_cmd	wc;
	char	*buff;
	int		log_fd;

	log_fd = open("./results_5.log", O_WRONLY | O_APPEND);
	buff = ft_strjoin(stack, ": ");
	
	//Write the input in result.log
	write(log_fd, buff, ft_strlen(buff) + 2);
	
	//pipe ps and checker/wc
	assign_cmd_fds(&ps, &checker, &wc, log_fd);

	//Execute push_swap
	ps.pid = fork();
	if (ps.pid == 0)
		exec_ps(ps, stack);

	//Execute checker: will print to STDOUT, only for personal reference
	checker.pid = fork();
	if (checker.pid == 0)
		exec_checker(checker, stack);

	//Execute wc: output will be redirected to results.log
	wc.pid = fork();
	if (wc.pid == 0)
		exec_wc(wc, log_fd);

	tester_cleanup(&ps, &checker, &wc, log_fd);

	close(log_fd);
}

void	tester_cleanup(t_cmd *ps, t_cmd *checker, t_cmd *wc, int log_fd)
{
	close(log_fd);
	close(ps->out_fd);
	close(checker->in_fd);
	close(wc->in_fd);
	ps->out_fd = 0;
	checker->in_fd = 0;
	wc->in_fd = 0;
}

void	assign_cmd_fds(t_cmd *ps, t_cmd *checker, t_cmd *wc, int log_fd)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		exit(errno);
	ps->out_fd = pipe_fds[1];
	checker->in_fd = pipe_fds[0];
	wc->in_fd = pipe_fds[0];
	return ;
}

void	exec_ps(t_cmd ps, char *stack)
{
	char	*argv[] = {"./push_swap", stack, NULL};

	dup2(ps.out_fd, STDOUT_FILENO);
	close(ps.out_fd);
	execv(argv[0], argv);
	perror("exec_ps failed");
	exit(errno);
}

void	exec_checker(t_cmd checker, char *stack)
{
	char	*argv[] = {"./checker_Mac", stack, NULL};

	dup2(checker.in_fd, STDIN_FILENO);
	close(checker.in_fd);
	execv(argv[0], argv);
	perror("exec_checker failed");
	exit(errno);
}

void	exec_wc(t_cmd wc, int log_fd)
{
	char	*argv[] = {"/usr/bin/wc", "-l", NULL};

	dup2(wc.in_fd, STDIN_FILENO);
	close(wc.in_fd);
	dup2(log_fd, STDOUT_FILENO);
	close(log_fd);
	execv(argv[0], argv);
	perror("exec_wc failed");
	exit(errno);
}
