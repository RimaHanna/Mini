#include "minishell.h"

extern long long g_last_exit_status;

// exec_pipe: WITH RANIA
// exec_redirects: WITH RANIA
// cmd_binaries: WITH RANIA
/*
	Verification du type d'opérateur de l'instruction (1-PIPE, 2-NONE, ou autre)
	et appelle la fonction appropriée pour exécuter l'instruction
*/
void	exec_cmd(t_statement *current_node, t_data *data)
{
	signal(SIGINT, child_signals);
	if (current_node->operator == PIPE_OP)
		exec_pipe(current_node, data);
	else if (current_node->operator == NONE)
		exec_executables(current_node, data);
	else
		exec_redirects(current_node, data);
	exit(g_last_exit_status);
}

// SUITE FILE: cmd_binaries.c
/*
	if it is a builtin commande it will return true directly and it will 
	execute the builtin command
*/
void	exec_executables(t_statement *node, t_data *data)
{
	if (builtin(node, data))
		return ;
	cmd_binaries(node, data);
}

/*
	Cette fonction est responsable de l'exécution d'une ligne de commande. 
	Si la ligne de commande ne contient qu'une seule instruction, elle vérifie 
	d'abord si cette instruction est une commande interne en appelant builtin. 
	Si c'est le cas, elle exécute la commande interne. Sinon, elle effectue un 
	fork pour créer un nouveau processus et exécuter l'instruction à 
	l'intérieur de ce processus. Ensuite, elle attend que le processus enfant 
	se termine. Le statut de sortie est stocké dans temp_status, et si le 
	processus enfant s'est terminé normalement, elle met à jour 
	g_last_exit_status avec le code de sortie.
	La raison pour laquelle elle ne fait pas de fork pour une seule instruction 
	est l'efficacité. Les forks sont coûteux en termes de ressources système, 
	car ils créent un nouveau processus complet. Pour une seule instruction, 
	il est plus efficace de l'exécuter directement dans le même processus 
	parent, à moins qu'il ne soit nécessaire de créer un nouveau processus 
	pour des raisons de séparation ou d'isolation. Les commandes internes du 
	shell, telles que cd ou export, peuvent être exécutées efficacement dans 
	le même processus parent sans avoir besoin de créer un processus enfant 
	supplémentaire. C'est pourquoi la condition est là pour éviter le coût 
	inutile d'un fork lorsque cela n'est pas nécessaire.
	signal: It sets up a signal handler for the child process. Specifically, 
	it catches the SIGINT signal, which typically corresponds to pressing 
	Ctrl+C in the terminal.
	waitpid: After executing either the single statement or multiple statements,
	the parent process waits for any child process to finish using 
	waitpid (it listen the child process). 
	This function suspends the parent process until a child process terminates. 
	The status of the terminated process is stored in temp_status.
	WTERMSIG: the last if condition checks if the child process terminated 
	normally (not due to a signal) using WTERMSIG. If it terminated normally, 
	it updates the global variable g_last_exit_status with the exit status of 
	the child process, which is typically the exit code of the last executed 
	command.
	Shifting temp_status to the right by 8 bits means that we are discarding 
	the lower 8 bits of temp_status and keeping only the higher bits, which 
	correspond to the exit status of the child process.
*/
void	execute_lineofcommand(t_statement *statement_list, t_data *data)
{
	int		temp_status;

	if (parser_lstsize(statement_list) == 1)
	{
		if (is_builtin(statement_list))
			builtin(statement_list, data);
		else
		{
			if(fork() == 0)
			{
				signal(SIGINT, child_signals);
				exec_executables(statement_list, data);
			}
		}
	}
	else if (fork() == 0)
		exec_cmd(statement_list, data);
	waitpid(-1, &temp_status, 0);
	if (!WTERMSIG(temp_status))
		g_last_exit_status = temp_status >> 8;
}
