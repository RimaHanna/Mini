/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:20:52 by rmouhoub          #+#    #+#             */
/*   Updated: 2022/11/12 20:26:34 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	int	i;
	int	j;
	int	lenn;

	i = 0;
	lenn = (int)len;
	if ((int)len < 0)
		lenn = ft_strlen(big);
	if (!little[0])
		return ((char *)big);
	while (i < lenn && big[i])
	{
		j = 0;
		while (((i + j) < lenn) && (big[i + j] == little[j] && (big[i + j])))
		{
			j++;
			if (!little[j])
				return ((char *)&big[i]);
		}
	i++;
	}
	return (NULL);
}

/*
int	main(void)
{
	char	*s="heyolloyo";
	char	*f="";
	printf("le resltat:%s \n",ft_strnstr(s, f, 6));
	//printf("le resltat:%s ",strnstr(s, f,6));
printf("%p\n", ft_strnstr("asdf qwerty", "qwerty",6));
//printf("%p\n", strnstr("asdf qwerty", "qwerty",6));

printf("%p\n", ft_strnstr("", "wer", 3));
//printf("%s\n", strnstr("", "wer", 3));

printf("%p\n", ft_strnstr("asdfzxcvrty", "zxcv", 7));
//printf("%p\n", strnstr("asdf qwerty", "zxcv", 7));
 }*/