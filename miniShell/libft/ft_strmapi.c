/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:20:28 by rmouhoub          #+#    #+#             */
/*   Updated: 2022/11/07 18:00:02 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	size;
	char	*dest;

	i = 0;
	size = ft_strlen(s);
	dest = (char *)malloc (sizeof(char ) * size + 1);
	if (!dest || !s || !f)
		return (NULL);
	while (s[i])
	{
		dest[i] = f (i, s[i]);
		i++;
	}
	dest[size] = 0;
	return (dest);
}
