/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:18:41 by rmouhoub          #+#    #+#             */
/*   Updated: 2022/11/07 18:46:55 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*s_dup;

	i = 0;
	s_dup = (char *)malloc (sizeof (char) * (ft_strlen(s) + 1));
	if (!s_dup)
		return (NULL);
	while (s[i])
	{
		s_dup [i] = s[i];
		i++;
	}
	s_dup[i] = '\0';
	return (s_dup);
}
/*
#include<stdio.h>
#include<string.h>
int main (void)
{
	char *c;
	c = ft_strdup("");
	printf ("%p\n", c);
	char *c2;
	c = strdup("");
	printf ("%p\n", c);

	
	free (c);
	//free (c2);

	 //printf ("%p\n", c);
}*/