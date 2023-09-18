#include "minishell.h"

/**
 * Removes leading and trailing whitespace characters specified in the 'set' 
 * parameter from the given string 'line'.
 * 
 * @param line - The input string to be trimmed.
 * @param set - A string containing characters to be 
 * 				trimmed (e.g., " \t" trims spaces and tabs).
 * 
 * @return A dynamically allocated string containing the trimmed 'line'.
 *         The caller is responsible for freeing the returned memory.
 *         Returns NULL if 'line' or 'set' is NULL, or if memory allocation 
 * 		   fails.
 */
char	*trim_whitespace_from_edges(char *line, char const *set)
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

/**
 * Reads a line of input from the user, trims leading and trailing whitespace,
 * and returns the resulting string.
 * 
 * @return A dynamically allocated string containing the trimmed user input.
 *         The caller is responsible for freeing the returned memory.
 */
char	*read_and_trim_lineofcommand(void)
{
	char	*line;
	char	*trimed_line;
	const char	*prompt;

	prompt = "minishell$ ";
	line = readline(prompt);
	add_history(line);
	trimed_line = trim_whitespace_from_edges(line, " \t");
	return (trimed_line);
}
