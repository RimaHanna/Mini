/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 17:04:58 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/08/25 18:41:36 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long g_last_exit_status = 0;

/*
	clean the variable list
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

// rl_clear_history is from the history libray
void	destroy(t_data *data)
{
	rl_clear_history();
	if (data->envp_lst)
		variable_lst_clean(&data->envp_lst);
	if (data->head)
		parse_lst_clean(&data->head);
}

void	exit_shell(int exit_status, t_data *data)
{
	ft_putendl_fd("exit", STDOUT_FILENO);
	g_last_exit_status = exit_status;
	if (data)
		destroy(data);
	exit(g_last_exit_status);
}

/*
	if there is more than one argument other than ./minishell ... 
	we terminate_shell
*/
void	terminate_shell(t_data *data, char *msg, int exit_status)
{
	if (data)
		destroy (data);
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(exit_status);
}

/*
    Within the loop, we 
    call a function to read a line && print a prompt., 
    call a function to split the line into args,
    and execute the args.
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

/*
    Shell_loop(), that will loop, interpreting commands.
    We will have three main part in our project
        1) Read: Read the command from standard input.
        2) Parse: Separate the command string into a program and arguments.
        3) Execute: Run the parsed command.
*/
int main (int argc, char **argv, char **env)
{
    shell_loop(argc, argv, env);
    return (0);
}


// I SHOULD TEST THE INVLAID SYNTAX