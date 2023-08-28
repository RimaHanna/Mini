#include "minishell.h"

extern int global_status;

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

// Check for invalid syntax in the string.
/*
	This function examines the provided string for various cases of
	invalid syntax. It checks for unexpected tokens at the beginning or end
	of the string, or redirection operator at the ennd of the string,
	or the existence of 2 simultinious pipes or 2 oppposit redirection, or 
	any symbol or wildcard. 
*/
bool	invalid_syntax(char *line)
{
	size_t	i;
	bool	is_quote;

	i = 0;
	is_quote = false;
	if ((line[0] == PIPE) || (line[ft_strlen(line) - 1] == PIPE))
		return (unexpected_token(PIPE));
	if (is_instr(REDIRECTS, line[ft_strlen(line) - 1]))
		return (unexpected_token(line[ft_strlen(line) - 1]));
	while (line[i])
	{
		if (is_instr(QUOTES, line[i]))
			is_quote = !is_quote; // WE SWITCH VALUES
		if (!is_quote && ((line[i] == '<' && line[i + 1] == '>')
				|| (line[i] == '>' && line[i + 1] == '<')
				|| (line[i] == '|' && line[i + 1] == '|')))
			return (unexpected_token(line[i + 1]));
		else if (!is_quote && ((line[i] == '{' || line[i] == '}'
				|| line[i] == '(' || line[i] == ')' || line[i] == '['
				|| line[i] == ']' || line[i] == ';' || line[i] == '&'
				|| line[i] == '*')))
			return (unexpected_token(line[i]));
		i++;
	}
	return (false);	
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
	This function examines the provided input line for potential syntax errors 
	related to operators and quotes. It iterates through the line to identify
	operator characters, and within this process, it also considers the 
	presence of quoted sections to prevent treating characters within quotes 
	as operators.
*/
bool	invalid_syntax_in_operator(char *line)
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

/*
	This function checks the validity of user input in a shell program.
	It examines the input for empty strings, unclosed quotes, or syntax errors.
	If any of these issues are found, the function marks the input as invalid,
	performs cleanup, sets the exit status, and returns the validity status.
	false = 0;
	true = 1;
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
		else if (invalid_syntax(line) || invalid_syntax_in_operator(line))
			valid = false;
		if (valid == false) // IT ISN'T VALID
		{
			free(line);
			global_status = UNVALID_LINE;
		}
		return (valid);
	}