/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:13:29 by rmouhoub          #+#    #+#             */
/*   Updated: 2022/11/11 16:08:08 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	intlenth(long int n)
{
	int	counter;

	counter = 0;
	while (n != 0)
	{
		n /= 10;
		counter++;
	}
	return (counter);
}

void	fill_t(long int n, char *p)
{
	if (n != 0)
	{
		*p = (n % 10 + '0');
		fill_t (n / 10, p - 1);
	}
}

char	*ft_itoa(int n)
{
	char			*c;
	int				size;
	long int		nb;

	nb = n;
	if (n == 0)
		return (ft_strdup("0"));
	size = intlenth(nb) + (nb < 0);
	c = (char *)malloc(sizeof(char ) * size + 1);
	if (!c)
		return (NULL);
	if (nb > 0)
		fill_t (nb, c + (size - 1));
	else
	{
		nb = n;
		fill_t (-nb, c + (size - 1));
	}
	if (nb < 0)
		*c = '-';
	c[size] = '\0';
	return (c);
}
/*
#include <stdio.h>
int main (void){
	int n = -6;
	unsigned int cp = n;
	printf("%d\n", cp);
	//printf ("%d\n",intlenth(-8473974) );
	char *c = ft_itoa(-2147483648);
	// char p[10];
	// p = fill_t(10, c);
	 printf ("%s\n",c);

}
*/