#include "minishell.h"

extern long long	g_last_exit_status;

/**
 * Checks if there are any unclosed quotes in a given string.
 *
 * @param {char *} str - The input string to check for unclosed quotes.
 * @returns {int} - Returns 1 if there are unclosed quotes, 0 otherwise.
 */
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

/**
 * Reports an unexpected token error to the standard error output.
 *
 * @param {char} token - The unexpected token to report.
 * @returns {bool} - Always returns true after reporting the error.
 */
bool	unexpected_token(char token)
{
	ft_putstr_fd(UNEXPECTED_TOKEN, STDERR_FILENO);
	ft_putchar_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
	return (true);
}

/**
 * Checks if a given string contains any operator characters.
 *
 * @param {char *} line - The input string to check for operators.
 * @returns {bool} - Returns true if the string contains operators, false otherwise.
 */
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

/**
 * Checks the validity of user input in a shell program.
 *
 * @param line - The input line to be validated.
 * @param data - A pointer to the shell's data structure.
 *
 * @returns 1 if the input is valid, 0 if invalid.
 *
 * This function examines the input for empty strings, unclosed quotes,
 * and syntax errors. If any of these issues are found, the function marks
 * the input as invalid, performs cleanup, sets the exit status, and returns
 * the validity status.
 *
 * Validity Status:
 * - false (0) for invalid input.
 * - true (1) for valid input.
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
		g_last_exit_status = UNVALID_LINE;
	}
	return (valid);
}