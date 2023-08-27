/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:21:36 by rmouhoub          #+#    #+#             */
/*   Updated: 2022/11/13 15:43:52 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*my_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;

	i = 0;
	if (!dest || !src)
		return (NULL);
	while (n-- > 0 && i < ft_strlen(src))
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	((char *)dest)[i] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	size_t		mallocsize;

	if (!s)
		return (NULL);
	mallocsize = ft_strlen(s);
	if (start > mallocsize)
		return (ft_strdup(""));
	if (start + len > mallocsize)
		len = mallocsize - start;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (start-- > 0)
		s++;
	str = my_memcpy(str, s, len);
	return (str);
}
/*
#include <string.h>
#include <stdio.h>
int main (void)
{
	char *str = strdup("0123456789");
	char *s = ft_substr(str, 9, 10);
	printf("%s\n",s);
	printf("%d\n",ft_strncmp(s, "9", 1));
	//char csrc[100] = "hhkdjsuksncxmn";
	//char csrc2[100] = "hhkdjsuksncxmn";

	// ft_memmove(csrc+3, csrc+2, 0);
	// memmove (csrc2+3, csrc2+2, 0);
	printf("%s\n", ft_substr("tripouille", 0, 42000));
	//printf("%s", ft_substr2 (csrc2, 0, 90));
	return 0;
}*/