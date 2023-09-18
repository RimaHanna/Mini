#include "minishell.h"


/**
 * Check for invalid syntax in the provided string.
 *
 * These two functions examine the provided string for various cases of invalid
 * syntax. They check for unexpected tokens at the beginning or end of the
 * string, or a redirection operator at the end of the string, or the existence
 * of two simultaneous pipes or two opposite redirection operators, or any
 * symbol or wildcard.
 *
 * @param {string} line - The string to check for invalid syntax.
 * @returns {boolean} True if the string contains invalid syntax, otherwise
 * false.
 */
bool	invalid_pipe_syntax(char *line)
{
	if ((line[0] == PIPE) || (line[ft_strlen(line) - 1] == PIPE))
		return (unexpected_token(PIPE));
	if (is_instr(REDIRECTS, line[ft_strlen(line) - 1]))
	{
		ft_putendl_fd(RED_SYT_ERR, STDERR_FILENO);
		return (true);
	}
	return (false);	
}

/**
 * Check for invalid token syntax in the provided string.
 *
 * This function examines the provided string for invalid token syntax. It
 * checks for unexpected token pairs, such as '><', '><', or '||', outside of
 * quotation marks, and for various special symbols.
 *
 * @param {string} line - The string to check for invalid token syntax.
 * @returns {boolean} True if the string contains invalid token syntax,
 * otherwise false.
 */
bool	invalid_token_syntax(char *line)
{
	size_t	i;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	while (line[i])
	{
		if (is_instr(QUOTES, line[i]))
			in_quotes = !in_quotes;
		if (((line[i] == '>' && line[i + 1] == '<')
				|| (line[i] == '<' && line[i + 1] == '>')
				|| (line[i] == '|' && line[i + 1] == '|')) && !in_quotes)
			return (unexpected_token(line[i + 1]));
		else if ((line[i] == '{' || line[i] == '}'
				|| line[i] == '(' || line[i] == ')'
				|| line[i] == '[' || line[i] == ']'
				|| line[i] == ';' || line[i] == '&' || line[i] == '*')
			&& !in_quotes)
			return (unexpected_token(line[i]));
		i += 1;
	}
	return (false);
}

/**
 * Examines the provided input line for potential syntax errors related to 
 * operators and quotes. It iterates through the line to identify operator 
 * characters. During this process, it also considers the presence of quoted 
 * sections to prevent treating characters within quotes as operators.
 *
 * @param {char *} line - The input line to examine for syntax errors.
 *
 * @returns {bool} True if there are syntax errors, false otherwise.
 */
bool	invalid_operator_syntax(char *line)
{
	size_t	i;
	bool	in_quotes;

	i = 0;
	in_quotes = false;
	while (string_has_operator(&line[i]))
	{
		if (is_instr(QUOTES, line[i]))
			in_quotes = !in_quotes;
		if (is_instr(OPERATORS, line[i]) && !in_quotes)
		{
			if (line[i] == line[i + 1])
				i = i + 2;
			else
				i++;;
			if (line[i] == ' ')
			{
				while (line[i] && line[i] == ' ')
					i++;
				if (is_instr(OPERATORS, line[i]))
					return (unexpected_token(line[i]));
			}
			if (is_instr(OPERATORS, line[i]))
				return (unexpected_token(line[i]));
		}
		i++;
	}
	return (false);
}