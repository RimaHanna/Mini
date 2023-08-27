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
	char	*str;
	size_t	ls1;
	size_t	ls2;

	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	str = malloc(sizeof(char) *(ls1 + ls2 + 1));
	if (!str)
		return (NULL);
	if (!s1)
	{	
		str = ft_memcpy(str, s2, ls2);
		str[ls2] = '\0';
	}
	else
	{
		ft_memcpy(str, s1, ls1);
		ft_memcpy(str + ls1, s2, ls2);
		str[ls1 + ls2] = '\0';
	}
	free(s1);
	return (str);
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
