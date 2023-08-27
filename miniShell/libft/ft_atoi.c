/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:09:50 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/02/18 14:35:34 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	the_signe(const char *str)
{
	if (*str == '+')
		return (1);
	else
		return (-1);
}

long long int	ft_atoi_long(const char *str, long long int	*tab)
{
	long long int	signe;
	long long int	result;

	result = 0;
	signe = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '+' || *str == '-')
	{
		signe = the_signe(str);
		str++;
	}
	while (*str >= '0' && *str <= '9')
		result = (result * 10) + (*str++ - '0');
	if (*str)
	{
		free(tab);
		ft_printf("ERROR\n");
		exit(0);
	}
	return (result * signe);
}

int	ft_atoi(const char *str)
{
	int	signe;
	int	result;

	result = 0;
	signe = 1;
	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	if (*str == '+' || *str == '-')
	{
		signe = the_signe(str);
		str++;
	}
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			result = (result * 10) + (*str - '0');
		else
			break ;
		str++;
	}
	return (result * signe);
}
/*
#include <stdio.h>
#include <string.h>
int main ()
{
	printf("mon atoi : %d\n", ft_atoi("-\n\n\n\n\n\n46\b9 \n5d6"));
	printf("leur atoi : %d\n\n", atoi("-\n\n\n\n\n\n46\b9 \n5d6"));

	printf("mon atoi : %d\n", ft_atoi("\n\n\n\n\n\n-46\b9 \n5d6"));
	printf("leur atoi : %d\n\n", atoi("\n\n\n\n\n\n-46\b9 \n5d6"));

	printf("mon atoi : %d\n", ft_atoi("-\n\n\n\n\n\n+46\b9 \n5d6"));
	printf("leur atoi : %d\n\n", atoi("-\n\n\n\n\n\n+46\b9 \n5d6"));

	printf("mon atoi : %d\n", ft_atoi("\n\n\n\n\n\n-\n\n46\b9 \n5d6"));
	printf("leur atoi : %d\n\n", atoi("\n\n\n\n\n\n-\n\n46\b9 \n5d6"));

	printf("mon atoi : %d\n", ft_atoi("546:5"));
	printf("leur atoi : %d\n\n", atoi("546:5"));
}
*/