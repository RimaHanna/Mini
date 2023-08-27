/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:19:43 by rmouhoub          #+#    #+#             */
/*   Updated: 2022/11/12 19:55:31 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	countlen2(char *dest, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (dest[i] && i < size)
		i++;
	return (i);
}

char	*ft_strncat(char *dest, const char *src, unsigned int nb)
{
	unsigned int	len;
	unsigned int	i;

	i = 0;
	len = ft_strlen(dest);
	if (nb == 0 || ft_strlen(src) == 0)
		return (dest);
	while (nb != 0 && src[i])
	{
		dest[len] = src[i];
		len++;
		i++;
		nb--;
	}
	dest[len] = 0;
	return (dest);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	size_d;
	size_t	size_s;
	size_t	temp;

	if (!size)
		return (ft_strlen(src));
	size_s = ft_strlen(src);
	size_d = countlen2(dest, size);
	if (size_d == size)
		return (size_s + size_d);
	else
	{
		temp = size - size_d;
		dest = ft_strncat (dest, src, temp - 1);
		return (size_d + size_s);
	}
}
