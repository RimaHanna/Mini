#include "minishell.h"
/*
	trim characters specified in the set parameter from the beginning
	and end of a string s1
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
