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

int global_status = 0;

/*
	trim characters specified in the set parameter from the beginning
	and end of a string s1
*/
char	*trim_free(char *line, char const *set)
{
	size_t	beg;
	size_t	end;
	char	*trimmed_str;

	beg = 0;
	if (!line || !set)
		return (NULL);
	while (line[beg] != '\0' && ft_strchr(set, line[beg]) != NULL)
		beg++;
	end = ft_strlen(line + beg);
	while (end > beg && ft_strchr(set, line[(beg + end) - 1]) != NULL)
		end--;
	trimmed_str = malloc((end + 1) * sizeof(char));
	if (!trimmed_str)
		return (NULL);
	ft_strncpy(trimmed_str, (line + beg), end);
	free(line);
	return (trimmed_str);
}

/*
	Have the string wrote in the command line without anyspaces at the 
	beginning and the end o the line in order to imitate the function of shell
	when displaying the history // it wasnt' needed for the add_history,
	but i will keep it because it facilite the division of the string after
*/
char	*trim_line(void)
{
	char	*line;
	char	*trimed_line;
	const char	*prompt;

	prompt = "minishell$ ";
	line = readline(prompt);
	add_history(line);
	trimed_line = trim_free(line, " \t");
	return (trimed_line);
}
/*
void	v_lstclear(t_vlst **head)
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
*/


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
	global_status = exit_status;
	if (data)
		destroy(data);
	exit(global_status);
}

/*
	if there is more than one argument other than ./minishell ... 
	we exit_all
*/
void	exit_all(t_data *data, char *msg, int exit_status)
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
    char    *line;
	t_data	data;
    t_statement *statement_list;

	(void)env;
	if (argv && argc > 1)
		exit_all(NULL, ERROR_MESSAGE, EXIT_FAILURE);
// ADD THE SETUP
    while (1)
    {
        line = trim_line();
		if (!valid_line(line, &data))
			continue;
		line = expander(line, &data);
		if (!line[0])
		{
			free(line);
			continue;
		}
		statement_list = parser(line);
		data.head = statement_list;
//		execute_type(statement_list, &data);
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