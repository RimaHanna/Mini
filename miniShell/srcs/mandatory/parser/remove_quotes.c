#include "minishell.h"

/**
 * Calculates the size of a string without counting characters inside quotes.
 *
 * @param {char *} parsed - The input string to calculate the size for.
 *
 * @returns {size_t} The size of the string without characters inside quotes.
 */
size_t	size_without_quotes(char *parsed)
{
	size_t	size;
	size_t	i;
	char	quote;

	i = 0;
	size = 0;
	while (parsed[i])
	{
		while (parsed[i] && (!is_instr(QUOTES, parsed[i])))
		{
			i++;
			size++;
		}
		if (!parsed[i])
			break;
		quote = parsed[i++];
		while (parsed[i] && (parsed[i] != quote))
		{
			i++;
			size++;
		}
		quote = 0;
	}
	return (size);
}

/**
 * Creates a new string without characters inside quotes from the given input.
 *
 * @param {char *} parsed - The input string to remove characters from.
 *
 * @returns {char *} A new string with characters inside quotes removed.
 */
char	*str_without_quotes(char *parsed)
{
	size_t	i;
	size_t	j;
	char	quote;
	char	*unquoted_parsed;

	i = 0;
	j = 0;
	quote = '\0';
	unquoted_parsed = malloc(sizeof(char) * (size_without_quotes(parsed) + 1));
	while (parsed[i])
	{
		while (parsed[i] && (!is_instr(QUOTES, parsed[i])))
			unquoted_parsed[j++] = parsed[i++];
		if (!parsed[i])
			break;
		quote = parsed[i];
		i++;
		while (parsed[i] && (parsed[i] != quote))
			unquoted_parsed[j++] = parsed[i++];
		quote = '\0';
	}
	unquoted_parsed[j] = '\0';
	free (parsed);
	return (unquoted_parsed);
}
