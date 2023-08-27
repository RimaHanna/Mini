# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/10 16:09:23 by rmouhoub          #+#    #+#              #
#    Updated: 2023/02/16 12:10:53 by rmouhoub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_memset.c \
			  ft_bzero.c \
			  ft_memcpy.c \
			  ft_memmove.c \
			  ft_memchr.c \
			  ft_memcmp.c \
			  ft_strlen.c \
			  ft_strlcpy.c \
			  ft_strlcat.c \
			  ft_strchr.c \
			  ft_strrchr.c \
			  ft_strnstr.c \
			  ft_strncmp.c \
			  ft_atoi.c \
			  ft_isalpha.c \
			  ft_isdigit.c \
			  ft_isalnum.c \
			  ft_isascii.c \
			  ft_isprint.c \
			  ft_toupper.c \
			  ft_tolower.c \
			  ft_calloc.c \
			  ft_strdup.c \
			  ft_substr.c \
			  ft_strjoinn.c \
			  ft_strtrim.c \
			  ft_striteri.c \
			  ft_split.c \
			  ft_itoa.c \
			  ft_strmapi.c \
			  ft_putchar_fd.c \
			  ft_putstr_fd.c \
			  ft_putendl_fd.c \
			  ft_putnbr_fd.c \
			  ft_strcontain.c \
			  ft_lstlast_free.c\
			  ft_printf.c \
			  ft_printf_util.c \
			  ft_lstnew.c \
			  ft_lstadd_front.c \
			  ft_lstsize.c \
			  ft_lstlast.c \
			  ft_beforlast.c \
			  ft_lstadd_back.c \
			  ft_lstdelone.c \
			  ft_lstclear.c \
			  get_next_line_utils.c \
			  get_next_line.c \
			  ft_lstiter.c
			  
NAME	= libft.a

OBJS	= ${SRCS:.c=.o}

HEADERS	= ./

CFLAGS = -Wall -Wextra -Werror


all : ${NAME}

${NAME} : ${OBJS}
		ar rcs ${NAME} ${OBJS}

.c.o	:
		gcc -Wall -Wextra -Werror -I ${HEADERS} -c $< -o ${<:.c=.o}
		
so:
	gcc -nostartfiles -shared -o libft.so ${CFLAGS} ${SRCS}

clean :
		rm -rf ${OBJS}

fclean : clean
		rm -rf ${NAME}

re : fclean all
