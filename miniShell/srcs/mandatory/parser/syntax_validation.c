#include "minishell.h"

extern long long	global_status;

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

bool	unexpected_token(char token)
{
	ft_putstr_fd(UNEXPECTED_TOKEN, STDERR_FILENO);
	ft_putchar_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (true);
}

bool	string_has_operator(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (is_instr(OPERATORS, line[i]))
			return (true);
		i += 1;
	}
	return (false);
}

/*
	This function checks the validity of user input in a shell program.
	First the function will check the return of readline (man readline) if it
	is NULL, in this case we have to free the line and exit
	The exit_success has the value of 0
	Than it examines the input for empty strings, unclosed quotes, or syntax
	errors.
	If any of these issues are found, the function marks the input as invalid,
	performs cleanup, sets the exit status, and returns the validity status.
	false = 0;
	true = 1;
*/
	bool	valid_lineofcommand(char *line, t_data *data)
	{
		bool	valid;

		valid = true;
		if (line == NULL)
		{
			free(line);
			exit_shell(EXIT_SUCCESS, data);
		}
		if (*line == '\0')
			valid = false;
		else if (unclosed_quote(line))
		{
			ft_putendl_fd(UNCLOSED_QUOTE, STDERR_FILENO);
			valid = false;
		}
		else if (invalid_pipe_syntax(line) || invalid_operator_syntax(line)
				|| invalid_token_syntax(line))
			valid = false;
		if (valid == false) // IT ISN'T VALID
		{
			free(line);
			global_status = UNVALID_LINE;
		}
		return (valid);
	}