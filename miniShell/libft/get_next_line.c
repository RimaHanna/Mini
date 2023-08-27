/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:33:11 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/02/18 18:16:20 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include<stdio.h> 
#include <fcntl.h> 

char	*get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	reached_eol(char *str)
{
	if (str == NULL)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*reading(int fd, char *reading_buf, char *stock)
{
	int	readed;

	readed = 1;
	while (readed > 0 && !reached_eol(stock))
	{
		readed = read(fd, reading_buf, BUFFER_SIZE);
		if (readed < 0)
		{
			return (NULL);
		}
		reading_buf [readed] = '\0';
		stock = ft_strjoin(stock, reading_buf);
	}
	return (stock);
}

char	*get_after_line(char *str)
{
	int		i;
	int		j;
	char	*buf;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free (str);
		str = NULL;
		return (NULL);
	}
	buf = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!buf)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		buf[j++] = str[i++];
	buf[j] = '\0';
	free (str);
	return (buf);
}

char	*get_next_line(int fd, int boolean)
{
	char		*reading_buf;
	char		*line;
	static char	*stock;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (boolean)
		return (free(stock), NULL);
	reading_buf = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!reading_buf)
		return (NULL);
	stock = reading(fd, reading_buf, stock);
	if (stock == NULL)
	{
		free(stock);
		free(reading_buf);
		return (NULL);
	}
	line = get_line(stock);
	stock = get_after_line(stock);
	free(reading_buf);
	return (line);
}

// #include <stdio.h>
// #include <fcntl.h>

// int main (int argc, char *argv[])
// {
// 	(void )argc;
// 	(void )argv;

// 	char *buf;
// 	//int fd = open (argv[1], O_RDONLY);
// 	while ((buf = get_next_line(0)))
// 	{
// 		printf("%s", buf);
// 		free(buf);	
// 	}
// }