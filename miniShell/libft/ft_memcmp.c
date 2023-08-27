/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:15:31 by rmouhoub          #+#    #+#             */
/*   Updated: 2022/11/07 17:31:15 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1p;
	const unsigned char	*s2p;

	s1p = (const unsigned char *)s1;
	s2p = (const unsigned char *)s2;
	while (n-- > 0)
	{
		if (*s1p != *s2p)
			return (*s1p - *s2p);
		s1p++;
		s2p++;
	}
	return (0);
}
/*
#include <string.h>
#include <stdio.h>
int main(int argc ,char argv[])
{
	//void *t1 [] = "hloo";
	//void *t2 [] = "dfds";
	//char *r =ft_strncmp(t, 66, 3);
	printf("output : %s \n",ft_memcmp("fs", "fs", 1));
	printf("output : %s \n",memcmp("fs", "fs", 1));
}
*/
