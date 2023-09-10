#include <minishell.h>

/**
 * Checks if a character exists in the given string.
 *
 * @param {const char *} str - The string to search in.
 * @param {char} chr - The character to look for.
 *
 * @return {bool} True if the character exists in the string, false otherwise.
 */
bool	is_instr(const char *str, char chr)
{
	int i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (chr == str[i])
	    	return (true);
		i++;
	}
	return (false);
}