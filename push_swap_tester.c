#include "./incl/push_swap.h"
#include <fcntl.h>
#include <errno.h>

#define TEMP_PATH "./ps_tester.tmp"
#define LOG_5_PATH "./results_5.log"
#define MAX_MOVES 9

typedef struct	s_cmd {
	int		in_fd;
	int		out_fd;
	pid_t	pid;
}	t_cmd;


void 	execute_permutation(char *stack);
void	exec_ps(t_cmd ps, char *stack);
void	exec_checker(t_cmd ps, char *stack);
void	exec_wc(t_cmd wc);
void	tester_cleanup(t_cmd *ps, t_cmd *checker, t_cmd *wc, int log_fd);
void	wait_cmds(pid_t pid_ps, pid_t pid_checker, pid_t pid_wc);
void	write_report(void);

int	main(void)
{
	char	*curr_line;
	int		nl_pos;
	int		fd;

	fd = open("./5_permutations.txt", O_RDONLY);
	curr_line = get_next_line(fd);
	while (curr_line && ft_isdigit(curr_line[0]))
	{
		//Remove the '\n'
		nl_pos = strlen_c(curr_line, '\n');
		if (nl_pos > 0)
			curr_line[nl_pos - 1] = 0;
		// printf(MAGENTA"---> curr_line = '%s'\n"RESET_COL, curr_line);
		//Go to execute
		execute_permutation(curr_line);
		free (curr_line);
		curr_line = get_next_line(fd);
		printf(YELLOW"-->curr_line == %s\n"RESET_COL, curr_line);
	}
	close(fd);
	write_report();
	exit (0);
}

//Doesn't properly work bc I'm writing to and reading from the same fd
//Needs some rework.
void	write_report(void)
{
	char	*stack_input;
	char	*curr_line;
	char	*prev_line;
	int		log_fd;
	int 	curr_moves;

	log_fd = open(LOG_5_PATH, O_RDWR | O_APPEND);
	curr_line = get_next_line(log_fd);
	prev_line = NULL;
	stack_input = NULL;
	while (curr_line)
	{
		if (!ft_isdigit(curr_line[0]))
		{
			curr_moves = ft_atoi(curr_line);
			printf("atoi(curr_line) = %d\n", curr_moves);
			if (curr_moves > MAX_MOVES)
			{
				stack_input = ft_get_first_token(prev_line, ':');
				ft_putstr_fd("**nb_moves for : ", log_fd);
				ft_putstr_fd(stack_input, log_fd);
				ft_putstr_fd(" --> ", log_fd);
				ft_putnbr_fd(curr_moves, log_fd);
				ft_putchar_fd('\n', log_fd);
				free(stack_input);
			}
		}
		free(prev_line);
		prev_line = curr_line;
		curr_line = get_next_line(log_fd);
	}
	free(prev_line);
	close(log_fd);
}

void	execute_permutation(char *stack)
{
	t_cmd	ps;
	t_cmd	checker;
	t_cmd	wc;
	char	*buff;
	char	temp_fd;
	int		log_fd;
	int		status;

	log_fd = open(LOG_5_PATH, O_WRONLY | O_APPEND, 0644);
	if (log_fd == -1)
		log_fd = open(LOG_5_PATH, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	buff = ft_strjoin(stack, ": ");
	
	//Write the input in result.log
	write(log_fd, buff, ft_strlen(buff));
	close(log_fd);
	
	//Write everything to an intermediary file so that both checker and wc can
	//easily access it
	temp_fd = open(TEMP_PATH, O_CREAT | O_RDWR | O_APPEND, 0644);

	//Execute push_swap
	ps.out_fd = temp_fd;
	ps.pid = fork();
	if (ps.pid == 0)
		exec_ps(ps, stack);
	close(ps.out_fd);
	close(temp_fd);

	status = 0;
	waitpid(ps.pid, &status, 0);

	//Execute checker: will print to STDOUT, only for personal reference
	temp_fd = open(TEMP_PATH, O_RDONLY, 0644);
	printf(RED"temp_fd before exec_checker = %d\n"RESET_COL, temp_fd);
	dup2(temp_fd, STDIN_FILENO);
	// close(temp_fd);

	log_fd = open(LOG_5_PATH, O_WRONLY | O_APPEND);
	checker.out_fd = log_fd;
	checker.pid = fork();
	if (checker.pid == 0)
		exec_checker(checker, stack);
	close(checker.out_fd);
	close(temp_fd);

	waitpid(checker.pid, &status, 0);

	//Execute wc: output will be redirected to results.log
	temp_fd = open(TEMP_PATH, O_RDONLY, 0644);
	printf(RED"temp_fd before exec_wc = %d\n"RESET_COL, temp_fd);
	dup2(temp_fd, STDIN_FILENO);
	close(temp_fd);
	log_fd = open(LOG_5_PATH, O_WRONLY | O_APPEND);
	wc.out_fd = log_fd;
	wc.pid = fork();
	if (wc.pid == 0)
		exec_wc(wc);
	close(wc.out_fd);
	close(temp_fd);

	waitpid(wc.pid, &status, 0);
	tester_cleanup(&ps, &checker, &wc, log_fd);
	
	write(log_fd, "\n", 1);

}

void	wait_cmds(pid_t pid_ps, pid_t pid_checker, pid_t pid_wc)
{
	int	status;

	status = 0;
	printf(YELLOW"waiting for PID_ps : %d\n"RESET_COL, pid_ps);
	waitpid(pid_ps, &status, 0);
	printf(YELLOW"waiting for PID_wc : %d\n"RESET_COL, pid_wc);
	waitpid(pid_wc, &status, 0);
	printf(YELLOW"waiting for PID_checker : %d\n"RESET_COL, pid_checker);
	waitpid(pid_checker, &status, 0);

	sleep(1);
}

void	tester_cleanup(t_cmd *ps, t_cmd *checker, t_cmd *wc, int log_fd)
{
	close(log_fd);
	close(ps->in_fd);
	close(checker->in_fd);
	close(wc->in_fd);
	close(ps->out_fd);
	close(checker->out_fd);
	close(wc->out_fd);
	unlink(TEMP_PATH);
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

	dup2(checker.out_fd, STDOUT_FILENO);
	close(checker.out_fd);
	execv(argv[0], argv);
	perror("exec_checker failed");
	exit(errno);
}

void	exec_wc(t_cmd wc)
{
	char	*argv[] = {"/usr/bin/wc", "-l", NULL};

	dup2(wc.out_fd, STDOUT_FILENO);
	close(wc.out_fd);
	execv(argv[0], argv);
	perror("exec_wc failed");
	exit(errno);
}
