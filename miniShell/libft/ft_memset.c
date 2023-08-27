/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:16:21 by rmouhoub          #+#    #+#             */
/*   Updated: 2022/11/12 13:22:01 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = -1;
	while (++i < n)
		((char *)s)[i] = c;
	return (s);
}
/*
#include <stdio.h>
int main()
{
	//(void)argc;
    void *t [100];
    char *r =ft_memset(t, 66, 3);
    printf("output : %d %d %d \n", r[0], r[1], r[2]);
}
*/