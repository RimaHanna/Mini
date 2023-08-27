/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:48:13 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/02/16 14:10:56 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(char c)
{
	return (write(2, &c, 1));
}

int	ft_putnbr(unsigned long nb, unsigned long base, int up_do, int *counter)
{
	if (nb > base - 1)
		ft_putnbr((nb / base), base, up_do, counter);
	return ((*counter += ft_putchar((HEXA_DECIM[nb % base + (up_do * 16)]))));
}

int	ft_putstr(char *c)
{
	int	counter;

	if (!c)
		return (write(2, "(null)", 6));
	counter = 0;
	while (*c)
		counter += ft_putchar(*c++);
	return (counter);
}
