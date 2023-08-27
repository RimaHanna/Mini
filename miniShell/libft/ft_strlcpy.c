/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:20:00 by rmouhoub          #+#    #+#             */
/*   Updated: 2022/11/10 18:09:03 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
#include <string.h>
#include <stdio.h>
int main (void)
{
	char csrc[100] = "";
    char dest[100] = "";
	// char csrc2[100] = "d";
    // char dest2[100] = "hdsdsh";

    // ft_memmove(csrc+3, csrc+2, 0); 
    // memmove (csrc2+3, csrc2+2, 0);
	int i = ft_strlcpy(dest, csrc, 5); 
    printf("%d\n", i);
    //printf("%d", ft_strlcpy2 (dest2, csrc2, 0));
    return 0;
}*/
