#include "minishell.h"

/**
 * @brief Copy at most 'n' characters from 'src' to 'dest'.
 * 
 * This function copies characters from the 'src' string to the 'dest' string.
 * It will copy at most 'n' characters, ensuring the destination is 
 * null-terminated.
 * If 'src' is shorter than 'n', null characters are added to 'dest' 
 * to fill 'n' characters.
 * 
 * @param dest The destination string where characters are copied.
 * @param src The source string from which characters are copied.
 * @param n The maximum number of characters to copy.
 * 
 * @return A pointer to 'dest'.
 */
char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i += 1;
	}
	if (src[i] && i < n)
	{
		while (i < n)
			dest[i++] = '\0';
	}
	dest[i] = '\0';
	return (dest);
}