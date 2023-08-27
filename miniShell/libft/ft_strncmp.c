/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:20:45 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/02/16 18:19:04 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*st1;
	unsigned char	*st2;

	i = 0;
	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	while ((i < n) && (st2[i] || st1[i]))
	{
		if (st1[i] != st2[i])
			return (st1[i] - st2[i]);
		i++;
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
	printf("output : %d \n",ft_strncmp("", "", 0));
	printf("output : %d \n",strncmp("", "", 0));
}*/
