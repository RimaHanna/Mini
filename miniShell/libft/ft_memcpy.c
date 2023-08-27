/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:15:40 by rmouhoub          #+#    #+#             */
/*   Updated: 2022/11/12 19:42:51 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (n-- > 0)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}
/*

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*csrc;
	char		*cdest;

	csrc = (char *)src;
	cdest = (char *)dest;
	i = 0;
	if (!dest || !src)
		return (NULL);
	while (cdest[i] && n-- > 0)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (cdest);
}

#include <string.h>
#include <stdio.h>
int main (void)
{
	char csrc[100] = "hhhhllll";
	//char csrc2[100] = "hhhhllll";

	// ft_memmove(csrc+3, csrc+2, 0);
	// memmove (csrc2+3, csrc2+2, 0);
	char *c=ft_memcpy(csrc, "kjshcs", 2);
	printf("%s\n",c);
	//printf("%s", memcpy (csrc2, "k", 2));
	return 0;
}*/