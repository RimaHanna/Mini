#include "minishell.h"

long long g_last_exit_status = 0;

/**
 * @brief Clean the variable list.
 * 
 * This function is responsible for cleaning up a linked list of variables.
 * It iterates through the list and frees the memory associated with each node.
 * Finally, it sets the head of the list to NULL.
 * 
 * @param head - A pointer to a pointer to the head of the variable list.
 * @return void
 */
void	variable_lst_clean(t_vlst **head)
{
	t_vlst	*temp;
	t_vlst	*next_node;

	if (!head)
		return ;
	temp = *head;
	while (temp != NULL)
	{
		next_node = temp->next;
		free(temp->var_name);
		free(temp->var_value);
		free(temp);
		temp = next_node;
	}
	*head = NULL;
}

/**
 * @brief Clears shell history, and cleans up environment and statement list.
 *
 * @param data A pointer to the shell data structure.
 *             It holds environment variables and the statement list.
 */
void	destroy(t_data *data)
{
	rl_clear_history();
	if (data->envp_lst)
		variable_lst_clean(&data->envp_lst);
	if (data->head)
		parse_lst_clean(&data->head);
}

/**
 * @brief Exit the shell with a specified exit status.
 *
 * This function terminates the shell and prints "exit" to standard output.
 * It also updates the global exit status variable.
 *
 * @param exit_status The exit status code to use when exiting.
 * @param data A pointer to the shell data, can be NULL.
 */
void	exit_shell(int exit_status, t_data *data)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	g_last_exit_status = exit_status;
	if (data)
		destroy(data);
	exit(g_last_exit_status);
}

/**
 * @brief Terminate the shell with an error message and exit status.
 * 
 * If there are multiple arguments other than ./minishell... we invoke 
 * terminate_shell
 * 
 * @param data A pointer to the shell data structure (can be NULL).
 * @param {char *} msg The error message to display.
 * @param exit_status The exit status code to use when exiting the shell.
 */
void	terminate_shell(t_data *data, char *msg, int exit_status)
{
	if (data)
		destroy (data);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(exit_status);
}

/**
 * @brief Initializes the shell, configures signals, and initializes data 
 * structures.
 *
 * @param {int} argc Number of command-line arguments.
 * @param {char *} argv[] Array of command-line arguments.
 * @param {char **} env Array of environment variables.
 */
void    shell_loop(int argc, char *argv[], char **env)
{
    char    *lineofcommand;
	t_data	data;
    t_statement *statement_list;
	
	if (argv && argc > 1)
		terminate_shell(NULL, ERROR_MESSAGE, EXIT_FAILURE);
	init_shell(env, &data, &statement_list);
    while (1)
    {
        lineofcommand = read_and_trim_lineofcommand();
		if (!valid_lineofcommand(lineofcommand, &data))
			continue;
		lineofcommand = expander(lineofcommand, &data);
		if (!lineofcommand[0])
		{
			free(lineofcommand);
			continue;
		}
		statement_list = parser(lineofcommand);
		data.head = statement_list;
		execute_lineofcommand(statement_list, &data);
		clean_parsed(&statement_list, &data);
    }
}

int main (int argc, char **argv, char **env)
{
    shell_loop(argc, argv, env);
    return (0);
}