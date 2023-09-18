#include "minishell.h"

extern long long g_last_exit_status;

/**
 * Redirects standard output to a pipe and executes a command.
 *
 * @param {t_statement*} nd - The statement to execute.
 * @param {t_data*} data - The shell data.
 * @param {int} pdes[2] - The pipe descriptor (output).
 */
void	left_side(t_statement *nd, t_data *data, int pdes[2])
{
	close(STDOUT_FILENO);
	dup(pdes[1]);
	close(pdes[0]);
	close(pdes[1]);
	exec_cmd(nd, data);
}

/**
 * Redirects standard input from a pipe and executes a command.
 *
 * @param {t_statement*} nd - The statement to execute.
 * @param {t_data*} data - The shell data.
 * @param {int} pdes[2] - The pipe descriptor (input).
 */
void	right_side(t_statement *nd, t_data *data, int pdes[2])
{
	close(STDIN_FILENO);
	dup(pdes[0]);
	close(pdes[0]);
	close(pdes[1]);
	exec_cmd(nd, data);
}

/**
 * Executes a command with input and output redirection using pipes.
 *
 * Bytes written on pipedes[1] can be read on pipedes[0].
 * The `pipe` system call creates an interprocess communication (IPC) channel.
 * The pipe descriptors (file descriptors) for reading and writing are stored
 * in `read_pipe` and `write_pipe`.
 *
 * @param {t_statement*} node - The statement to execute.
 * @param {t_data*} data - The shell data.
 */
void	exec_pipe(t_statement *node, t_data *data)
{
	pid_t	child_pid;
	int		pipedes[2];
	int		temp_status;

	node->operator = NONE;
	if (pipe(pipedes) == -1)
		terminate_shell(data, PIPE_ERR, EXIT_FAILURE);
	child_pid = fork();
	if (child_pid == -1)
		terminate_shell(data, FORK_ERR, EXIT_FAILURE);
	if (child_pid == 0)
		left_side(node, data, pipedes);
	right_side(node->next, data, pipedes);
	close(pipedes[0]);
	close(pipedes[1]);
	waitpid(child_pid, &temp_status, 0);
	g_last_exit_status = temp_status >> 8;
}