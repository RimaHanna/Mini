/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:21:21 by rmouhoub          #+#    #+#             */
/*   Updated: 2022/11/13 15:44:27 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	char	*c;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size = ft_strlen(s1);
	while (size > 0 && ft_strchr(set, s1[size]))
		size--;
	c = ft_substr(s1, 0, size +1);
	return (c);
}

// #include <stdio.h>
// int main (void)
// {
// 	char csrc[100] = "";
// 	// char csrc2[100] = "";

// 	// ft_memmove(csrc+3, csrc+2, 0);
// 	// memmove (csrc2+3, csrc2+2, 0);
// 	// printf("%s\n", ft_strtrim("       tripouiuullr ", ""));
// 	// printf("%s", ft_strtrim2 (csrc2, ""));
// 	return 0;
// }