#include "minishell.h"

extern long long g_last_exit_status;

/**
 * Redirects input from the terminal until a specified delimiter is encountered.
 *
 * @param node - The statement node representing the command and arguments.
 */
void	redirect_input_until(t_statement *node)
{
	char	*buff;
	int		fd[2];

	pipe(fd);
	while (1)
	{
		buff = readline("> ");
		if (streq(buff, node->next->argv[0]))
			break ;
		ft_putendl_fd(buff, fd[1]);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(buff);
}

/**
 * Redirects input from a file to standard input.
 * We have 2 while with the same condition in order to do an additional
 * check and make sure that we have skipped all consecutive input redirection
 * operators.
 *
 * @param node - The statement node representing the command and arguments.
 */
void	redirect_input(t_statement *node)
{
	int		in_file;
	char	*error_msg_prefix;

	if (node->next->argv[0])
	{
		while (node->next->operator == INP_RDR_OP)
			node = node->next;
		while (node->next->operator == INP_RDR_OP)
			node = node->next;
		if (access(node->next->argv[0], F_OK) == 0)
		{
			in_file = open(node->next->argv[0], O_RDONLY, 0666);
			dup2(in_file, STDIN_FILENO);
		}
		else
		{
			error_msg_prefix = ft_strjoin("minishell: ", node->next->argv[0]);
			perror(error_msg_prefix);
			free(error_msg_prefix);
			g_last_exit_status = 2;
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * Redirects standard output to a file, creating or truncating it.
 *
 * @param node - The statement node representing the command and arguments.
 */
void	redirect_output(t_statement *node)
{
	close(STDOUT_FILENO);
	while (node->next->operator == OUT_RDR_OP
		|| node->next->operator == APP_RDR_OP)
	{
		if (node->operator == OUT_RDR_OP)
			open(node->next->argv[0], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (node->operator == APP_RDR_OP)
			open(node->next->argv[0], O_WRONLY | O_APPEND | O_CREAT, 0666);
		node = node->next;
		close(1);
	}
	if (node->operator == OUT_RDR_OP)
		open(node->next->argv[0], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (node->operator == APP_RDR_OP)
		open(node->next->argv[0], O_WRONLY | O_APPEND | O_CREAT, 0666);
}

/**
 * Executes redirections for a statement node and determines whether to execute 
 * a command or pipe to another process.
 *
 * @param node - The statement node representing the command and arguments.
 * @param data - The shell data structure.
 */
void	exec_redirects(t_statement *node, t_data *data)
{
	t_statement	*temp;

	temp = node;
	if (node->operator == INP_RDR_OP)
		redirect_input(node);
	else if (node->operator == MUL_RDR_OP)
		redirect_input_until(node);
	else
		redirect_output(node);
	temp->operator = NONE;
	while (node->operator != NONE && node->operator != PIPE_OP)
		node = node->next;
	if (node->operator == NONE)
		exec_cmd(temp, data);
	else
		exec_pipe(node, data);
}
