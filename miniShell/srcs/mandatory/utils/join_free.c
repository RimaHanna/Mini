#include "minishell.h"

/*
 * Concatenates two strings, s1 and s2, and returns a new string.
 * It also manages the memory deallocation of s1.
 *
 * @param s1 - The first string to concatenate.
 * @param s2 - The second string to concatenate.
 * @return A new string containing the concatenated s1 and s2,
 *         or NULL if either s1 or s2 is NULL or if memory allocation fails.
 */
char	*join_free(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*joined;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	joined = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (j < len_s1)
		joined[i++] = s1[j++];
	j = 0;
	while (j < len_s2)
		joined[i++] = s2[j++];
	joined[i] = '\0';
	free(s1);
	return (joined);
}
