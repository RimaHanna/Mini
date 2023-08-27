/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:15:59 by rmouhoub          #+#    #+#             */
/*   Updated: 2022/11/07 17:48:56 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, int n)
{
	char	*c_dest;
	char	*c_src;
	int		i;

	i = 0;
	c_dest = (char *)dest;
	c_src = (char *)src;
	if (!n || c_dest == c_src)
		return (c_dest);
	if (c_dest > c_src)
	{
		while (n-- > 0)
			*(c_dest + n) = *(c_src + n);
	}
	else
	{
		while (i++ < n)
			*(c_dest + i - 1) = *(c_src + i - 1);
	}
	return (c_dest);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	char csrc[100] = "Hllydays";
	char csrc2[100] = "Hllydays";

	// ft_memmove(csrc+3, csrc+2, 0);
	// memmove (csrc2+3, csrc2+2, 0);
	printf("%s\n", ft_memmove(csrc, csrc+2, 18));
	printf("%s", memmove (csrc2, csrc2+2, 18));
	return 0;
}*/