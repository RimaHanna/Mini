/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:19:03 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/02/16 12:08:47 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"

char	*ft_strjoinn(char const *s1, char const *s2)
{
	char	*str;
	size_t	ls1;
	size_t	ls2;

	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (ls1 + ls2 + 1));
	if (!str || !s1 || !s2)
		return (NULL);
	ft_memcpy(str, s1, ls1);
	ft_memcpy(str + ls1, s2, ls2);
	str[ls1 + ls2] = '\0';
	return (str);
}

char	*ft_strjoine(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (!res || !s1 || !s2)
		return (NULL);
	i = 0;
	j = -1;
	while (s1[++j])
		res[j] = s1[j];
	i = 0;
	res[j++] = '/';
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	return (res);
}

/*
#include <string.h>
#include <stdio.h>
int main (void)
{
	char *csrc = "hhkdjsuksncxmn";
	char *csrc2 = ":::";

	// ft_memmove(csrc+3, csrc+2, 0);
	// memmove (csrc2+3, csrc2+2, 0);
	
	printf("%s\n", ft_strjoin(csrc,csrc2));
	//printf("%s", ft_strjoin ("cd", "vxcs"));
	return 0;
}
*/