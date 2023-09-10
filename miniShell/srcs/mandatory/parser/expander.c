#include "minishell.h"

extern long long	g_last_exit_status;

/**
 * This code is essential for expanding variables and managing the exit status 
 * within a minishell project, allowing users to work with environment variables 
 * and special shell variables like $?
 
*/

/**
 * Calculates the size (number of digits) of the exit status converted to a 
 * string.
 *
 * @return The size of the exit status string.
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


/**
 * Expands the exit status ($?) by converting it to a string and copying it
 * into the expanded input string.
 *
 * @param expanded_input_at_i - Pointer to the expanded input string where the
 *                              exit status will be copied.
 * @param i - Pointer to the index indicating the current position in the input.
 * @return The length of the expanded exit status string that was copied.
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

/**
 * Initializes variables used for parsing input.
 *
 * @param i - A pointer to the index variable.
 * @param size - A pointer to the size variable.
 * @param in_quotes - A pointer to the flag indicating if within single quotes.
 * @param in_dquotes - A pointer to the flag indicating if within double quotes.
 */
void	init_vars(size_t *i, size_t *size, bool *in_quotes, bool *in_dquotes)
{
	*i = 0;
	*size = 0;
	*in_quotes = false;
	*in_dquotes = false;
}

/**
 * Calculates the total size of the expanded input by iterating through the 
 * input string.
 * This function takes into account quotes and variables to determine the 
 * final size.
 *
 * @param {char *} input - The input string to expand and calculate the size 
 * for.
 * @param {t_data *} data - A pointer to shell data, which may be used for 
 * variable expansion.
 * @returns {int} The total size of the expanded input.
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

/**
 * Expand an input command line by replacing variables and handling quotes.
 *
 * This function iterates through the input string, handling single and double 
 * quotes as well as variables, and creates an expanded input string. 
 * Variables are identified by the '$' sign followed by their
 * names, e.g., $NAME.
 *
 * @param input - The input command line to expand.
 * @param data - A pointer to the shell's data structure, which contains 
 * variable values.
 *
 * @return A newly allocated expanded input string.
 *
 * @example
 * Suppose you have the following input string:
 * "Hello, $NAME! Your age is $AGE years old."
 * Let's assume that:
 * $NAME is assigned the value "John".
 * $AGE is assigned the value 30.
 * The `expander` function will perform variable expansion and return the  
 * following expanded string:
 * "Hello, John! Your age is 30 years old."
 *
 * @code
 * // Example usage:
 * char *input = "HELLO $USER";
 * char *expanded = expander(input, &shell_data);
 * // expanded will contain "HELLO rima" based on variable values.
 * @endcode
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
