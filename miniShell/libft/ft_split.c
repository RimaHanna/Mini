/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:17:39 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/03/18 17:05:04 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_incharset(char charset, char c)
{
	return (charset == c);
}

int	countwords(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (is_incharset(c, str[i]) && str[i])
			i++;
		if (!is_incharset(c, str[i]) && str[i])
			count++;
		while (str[i] && !is_incharset(c, str[i]))
			i++;
	}
	return (count);
}

char	*put_intab(char const *str, char c, int *i)
{
	int		i2;
	int		k;
	char	*res;

	i2 = 0;
	k = 0;
	while (is_incharset(c, str[*i]) && str[*i])
		(*i)++;
	while (!is_incharset(c, str[*i + i2]) && str[*i + i2])
		i2++;
	res = malloc(sizeof(char) * i2 + 1);
	if (!res)
		return (NULL);
	while (k < i2)
	{
		res[k++] = str[*i];
		(*i)++;
	}
	res[k] = '\0';
	return (res);
}

static void	ft_free_arr(char **s, int i)
{
	while (i--)
		free(s[i]);
	free(s);
}

char	**ft_split(char const *str, char c)
{
	int		i;
	int		lensp;
	char	**split;
	int		j;

	j = 0;
	i = 0;
	lensp = countwords(str, c);
	split = malloc(sizeof(char *) * (lensp + 1));
	if (!split)
		return (NULL);
	while (i < lensp)
	{
		split[i] = put_intab(str, c, &j);
		if (!split[i])
		{
			ft_free_arr(split, i - 1);
			return (0);
		}
		i++;
	}
	split[i] = 0;
	return (split);
}
/*
int    main(int argc, char *argv[])
{
	char    **res;
	char    **res1;

	int        i;

	i = 0;
	(void)argc;
	res = ft_split(argv[1],'x');
	while (res1[i])
	{
		printf("res[%i] = %s\n", i, res[i]);
		i++;
	}
	ft_free_arr(res, 0);
	return (0);
}*/