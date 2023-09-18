/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:27:37 by rmouhoub          #+#    #+#             */
/*   Updated: 2022/11/29 13:44:43 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (*s++)
		len++;
	return (len);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*csrc;
	char	*cdest;

	i = 0;
	csrc = (char *)src;
	cdest = (char *)dest;
	while (csrc[i] && i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	while (i < n)
	{
		cdest[i] = '\0';
		i++;
	}
	return (cdest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*final_str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	final_str = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	i = 0;
	j = 0;
	if (final_str == NULL)
		return (NULL);
	while (j < len_s1)
		final_str[i++] = s1[j++];
	j = 0;
	while (j < len_s2)
		final_str[i++] = s2[j++];
	final_str[i] = '\0';
	return (final_str);
}

// char	*ft_strdup(const char *s)
// {
// 	int		i;
// 	char	*s_dup;

// 	i = 0;
// 	s_dup = (char *)malloc (sizeof (char) * (ft_strlen(s) + 1));
// 	if (!s_dup)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		s_dup [i] = s[i];
// 		i++;
// 	}
// 	s_dup[i] = '\0';
// 	return (s_dup);
// }
