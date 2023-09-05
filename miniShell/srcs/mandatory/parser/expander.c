#include "minishell.h"

extern long long	g_last_exit_status;

/*
	This code is essential for expanding variables and managing the 
	exit status within a minishell project, allowing users to work with 
	environment variables and special shell variables like $?
*/


/*
	This function calculates the size (number of digits) of the exit status 
	converted to a string.
	1) Change the exit_status from an integer to an array with ft_llinttoarray 
		and save it in an array
	2) Bring the size of the array with ft_strlen
	3) Return the size
*/
size_t	exit_status_size(void)
{
	char	*exit_status;
	size_t	size;

	exit_status = ft_llinttoarray(g_last_exit_status);
	size = ft_strlen(exit_status);
	free(exit_status);
	return (size);
}


/*
	This function expands the exit status ($?) by converting it to a string
	and copying it into the expanded input string.
*/
size_t	expand_exit_status(char *expanded_input_at_i, size_t *i)
{
	char	*exit_status;
	size_t	j;

	*i += 2;
	exit_status = ft_llinttoarray(g_last_exit_status);
	j = 0;
	while (exit_status[j])
	{
		expanded_input_at_i[j] = exit_status[j];
		j += 1;
	}
	free(exit_status);
	return (j);
}

void	init_vars(size_t *i, size_t *size, bool *in_quotes, bool *in_dquotes)
{
	*i = 0;
	*size = 0;
	*in_quotes = false;
	*in_dquotes = false;
}

/*
	This function calculates the total size of the expanded input by 
	iterating through the input string.
	It takes into account quotes and variables to calculate the final size.
*/
int	expanded_size(char *input, t_data *data)
{
	size_t	i;
	size_t	size;
	bool	in_quotes;
	bool	in_dquotes;

	init_vars(&i, &size, &in_quotes, &in_dquotes);
	while (input[i])
	{
		if (input[i] == '\"' && !in_quotes)
			in_dquotes = !in_dquotes;
		if (input[i] == '\'' && !in_dquotes)
			in_quotes = !in_quotes;
		if ((input[i] == '$' && input[i + 1] == '?') && !in_quotes)
		{
			size = size + exit_status_size() - 1;
			i++;
		}
		else if (input[i] == '$' && !in_quotes)
			size = size + expand_size(&(input[i]), &i, data) - 1;
		else
			i++;
		size++;
	}
	return (size);
}


/*
	This is the main function responsible for expanding an input command line.
	It iterates through the input, handling quotes and variables, and creates 
	an expanded input string.
	Example:
	Suppose you have the following input string:
	"Hello, $NAME! Your age is $AGE years old."
	Let's assume that:
	$NAME is assigned the value "John".
	$AGE is assigned the value 30.
	Expander function will perform variable expansion and return the following 
	expanded string:
	"Hello, John! Your age is 30 years old."
	CODE EXPLANATION:
	input: HELLO $USER
	output: HELLO rima
	in the expander code it will be filling HELLO, when it reach the $sign,
	the rest of the string will be filled in function get_varvalue_fromvlst
*/
char	*expander(char *input, t_data *data)
{
	size_t	i;
	size_t	j;
	bool	in_quotes;
	bool	in_dquotes;
	char	*expanded_input;

	init_vars(&i, &j, &in_quotes, &in_dquotes);
	expanded_input = malloc((expanded_size(input, data) + 1) * sizeof(char));
	while (input[i])
	{
		if (input[i] == '\"' && !in_quotes)
			in_dquotes = !in_dquotes;
		if (input[i] == '\'' && !in_dquotes)
			in_quotes = !in_quotes;
		if (input[i] == '$' && input[i + 1] == '?' && !in_quotes)
			j = j + expand_exit_status(&(expanded_input[j]), &i);
		else if (input[i] && input[i] == '$' && !in_quotes)
			j = j + expand_variable(&(expanded_input[j]), input, &i, data);
		else
			expanded_input[j++] = input[i++];
	}
	expanded_input[j] = '\0';
	free(input);
	return (expanded_input);
}
