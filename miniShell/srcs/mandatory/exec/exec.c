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
	PREDEFINED MACROS FOR FD
	STDIN_FILENO // return 0 // standard input stream
	STDERR_FILENO // return 2 // standard error stream
	STDOUT_FILENO // return 1 // standard output stream
*/


// UTILS or LIBFT
char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i += 1;
	}
	if (src[i] && i < n)
	{
		while (i < n)
			dest[i++] = '\0';
	}
	dest[i] = '\0';
	return (dest);
}

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
	when displaying the history
*/
char	*trim_line(void)
{
	char	*line;
	char	*trimed_line;
	const char	*prompt;

	prompt = "minishell$ ";
	line = readline(prompt);
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

int	unclosed_quote(char *str)
{
	char	last_opened;
	
	last_opened = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '"')
		{
			if (last_opened == 0)
				last_opened = *str;
			else if (*str == last_opened)
				last_opened = 0;
		}
		str++;
	}
	if (last_opened)
		return (1);
	else
		return (0);
} 

/*
	This function checks the validity of user input in a shell program.
	It examines the input for empty strings, unclosed quotes, or syntax errors.
	If any of these issues are found, the function marks the input as invalid,
	performs cleanup, sets the exit status, and returns the validity status.
*/
	bool	valid_line(char *line)
	{
		bool	valid;

		valid = true;
		
		if (*line == '\0')
			valid = false;
		else if (unclosed_quote(line))
		{
			ft_putendl_fd(UNCLOSED_QUOTE, STDERR_FILENO);
			valid = false;
		}
		else if (invalid_syntax(line))
		{
			ft_putendl_fd(SYNTAX_ERROR, STDERR_FILENO);
			valid = false;
		}
		if (valid == false)
		{
			free(line);
			global_status = UNVALID_LINE;
		}
		return (valid);
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
    
    while (1)
    {
        line = trim_line();
		check_null_line(line);
		add_history(line);
		if (!valid_line(line))
			continue;
        //args = ft_split_line_into_args();
        //ft_exec();

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
