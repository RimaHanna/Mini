/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcontain.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:59:16 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/02/16 14:18:33 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcontain(const void *s1, const void *s2)
{
	int	i;

	i = 0;
	while (((char *)s1)[i])
	{
		if (((char *)s1)[i] == *((char *)s2))
			return (1);
		i++;
	}
	return (0);
}
