#include "minishell.h"

extern long long g_last_exit_status;

/**
 * Verifies the type of operator in the instruction (1-PIPE, 2-NONE, or other)
 * and calls the appropriate function to execute the instruction.
 *
 * @param current_node - Pointer to the statement node to be executed.
 * @param data - Pointer to the shell data structure containing environment 
 * variables.
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

/**
 * @brief Execute executable commands.
 *
 * This function checks if the provided command is a built-in command. If it
 * is a built-in command, it directly executes the command. Otherwise, it
 * executes external binaries.
 *
 * @param node  A pointer to the command node to be executed.
 * @param data  A pointer to the shell data structure.
 */
void	exec_executables(t_statement *node, t_data *data)
{
	if (builtin(node, data))
		return ;
	cmd_binaries(node, data);
}

/**
 * Execute a line of shell command(s).
 * 
 * This function is responsible for executing a line of shell command(s).
 * If the command line contains only a single instruction, it first checks if 
 * that instruction is an internal command by calling the `is_builtin` function. 
 * If it is an internal command, it executes the internal command. 
 * Otherwise, it forks to create a new process and runs the instruction inside 
 * that process. Afterward, it waits for the child process to terminate. The exit 
 * status of the child process is stored in `temp_status`, and if the child 
 * process terminated normally, it updates the global variable `g_last_exit_status` 
 * with the exit status.
 * 
 * The reason for not forking for a single instruction is efficiency. Forking is 
 * costly in terms of system resources because it creates a complete new process. 
 * For a single instruction, it's more efficient to run it directly within the 
 * same parent process unless it's necessary to create a new process for 
 * separation or isolation reasons. Shell's internal commands like `cd` or `export` 
 * can be executed efficiently within the same parent process without the need for 
 * an additional child process. This is why the condition is there to avoid the 
 * unnecessary cost of forking when it's not required.
 * 
 * @param statement_list - The list of parsed shell statements to execute.
 * @param data - The data structure containing shell environment and state.
 * @returns void
 * 
 * @remarks
 * - This function sets up a signal handler for the child process to catch the
 *   SIGINT signal, which corresponds to pressing Ctrl+C in the terminal.
 * - It uses the `waitpid` function to suspend the parent process until a child
 *   process terminates. The status of the terminated process is stored in 
 *   `temp_status`.
 * - The `WTERMSIG` macro is used to check if the child process terminated 
 *   normally (not due to a signal). If it terminated normally, this function 
 *   updates the global variable `g_last_exit_status` with the exit status of 
 *   the child process. Shifting `temp_status` to the right by 8 bits is done 
 *   to discard the lower 8 bits of `temp_status` and keep only the higher bits, 
 *   which correspond to the exit status of the child process.
 */
void	execute_lineofcommand(t_statement *statement_list, t_data *data)
{
	int		temp_status;

	if (parser_lstsize(statement_list) == 1)
	{
		if (!builtin(statement_list, data) && fork() == 0)
		{
			signal(SIGINT, child_signals);
			exec_executables(statement_list, data);
		}
	}
	else if (fork() == 0)
		exec_cmd(statement_list, data);
	waitpid(-1, &temp_status, 0);
	if (!WTERMSIG(temp_status))
		g_last_exit_status = temp_status >> 8;
}