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
	This function will check the return of readline (man readline) if it
	is NULL, if it is the case we have to free the line and exit, and in this
	case it shouldn't be registered in history.
	The exit_success has the value of 0
*/
void	check_null_line(char *line)
{
	if (line == NULL)
	{
		free(line);
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}

/*
    Within the loop, we 
    call a function to read a line && print a prompt., 
    call a function to split the line into args,
    and execute the args.
*/
void    shell_loop()
{
    char    *line;
	t_data	data;
    t_statement *statement_list;

(void)data;


// ADD THE SETUP
    while (1)
    {
        line = trim_line();
		check_null_line(line);
		if (!valid_line(line))
			continue;
// ADD THE EXPANDER WITH THE IF CONDITION
		statement_list = parser(line);
		data.head = statement_list;
//		execute_type(statement_list, &data);
        free(line);
        //free(args);
    }
}

/*
    Shell_loop(), that will loop, interpreting commands.
    We will have three main part in our project
        1) Read: Read the command from standard input.
        2) Parse: Separate the command string into a program and arguments.
        3) Execute: Run the parsed command.
*/
int main (int argc, char *argv[], char **env)
{
    (void)argc;
    (void)argv;
    (void)env;

    shell_loop();
    return (1);
}


// I SHOULD TEST THE INVLAID SYNTAX