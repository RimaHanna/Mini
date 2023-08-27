/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:44:58 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/02/16 14:13:16 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_print_d_or_i(va_list list, int base, int up_do, int *counter)
{
	long int	nb;

	nb = va_arg(list, int);
	if (nb < 0)
	{
		nb *= (-1);
		write(1, "-", 1);
		*counter = *counter + 1;
	}
	ft_putnbr(nb, base, up_do, counter);
	return (*counter);
}

int	ft_parse(const char c, va_list list)
{
	unsigned long	add;
	int				counter;

	counter = 0;
	if (c == 'c')
		return (ft_putchar(va_arg(list, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(list, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_print_d_or_i((list), 10, 0, &counter));
	else if (c == 'u')
		return (ft_putnbr(va_arg(list, unsigned int), 10, 0, &counter));
	else if (c == 'x' || c == 'X')
		return (ft_putnbr(va_arg(list, unsigned int), 16, (c == 'X'),
				&counter));
	else if (c == 'p')
	{
		add = (unsigned long)va_arg(list, void *);
		if (!add)
			return (write(1, "(nil)", 5));
		return ((write(1, "0x", 2) + ft_putnbr(add, 16, 0, &counter)));
	}
	return (ft_putchar(c));
}

int	ft_printf(const char *str, ...)
{
	int		counter;
	int		i;
	va_list	list;

	if (str == NULL)
		return (-1);
	va_start(list, str);
	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == '%')
			counter += ft_parse(str[++i], list);
		else
			counter += ft_putchar(str[i]);
		i++;
	}
	va_end(list);
	return (counter);
}
