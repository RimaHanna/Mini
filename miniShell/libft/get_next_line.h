/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:52:15 by rmouhoub          #+#    #+#             */
/*   Updated: 2023/02/18 17:22:25 by rmouhoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char		*get_line(char *str);
int			reached_eol(char *str);
char		*reading(int fd, char *reading_buf, char *stock);
char		*get_after_line(char *str);
char		*get_next_line(int fd, int boolean);
size_t		ft_strlen(const char *s);
char		*ft_strjoin(char *s1, char *s2);
void		*ft_memcpy(void *dest, const void *src, size_t n);

#endif