# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmouhoub <rmouhoub@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/25 17:11:56 by rmouhoub          #+#    #+#              #
#    Updated: 2023/08/25 18:27:42 by rmouhoub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
LINK = -I./includes
VPATH = srcs srcs/mandatory srcs/mandatory/exec srcs/mandatory/parser\
		srcs/mandatory/main srcs/mandatory/utils
RM = rm -rf
LIBFT = ./libft/libft.a

MAIN = main
EXEC = 
PARSE = remove_quotes
UTILS = is_instr

NAME = minishell
SRCS =	$(addsuffix .c, $(MAIN))\
		$(addsuffix .c, $(UTILS))\
		$(addsuffix .c, $(PARSER))\
			
OBJ_DIR = objs
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o minishell

$(LIBFT):
	$(MAKE) -C ./libft

$(OBJ_DIR):
	mkdir -p obj

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LINK)

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJ_DIR)
	$(RM) $(OBJS)
	
fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
	
re: fclean all

noleaks: re
	valgrind ./minishell

noleaksfull: re
	valgrind --leak-check=full --show-leak-kinds=all -s ./minishell

run: re
	./minishell

run2:
	./minishell

.PHONY: all clean fclean re run

.SILENT:
