CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
LINK = -I./includes
VPATH = srcs srcs/mandatory\
		srcs/mandatory/parser srcs/mandatory/utils srcs/mandatory/call\
		srcs/mandatory/setup
RM = rm -rf
LIBFT = ./libft/libft.a

UTILS = ft_strncpy is_instr ft_lltoa
PARSER = remove_quotes invalid_syntax parser clean_parsed expander
CALL = 
SETUP = init_and_setup_shell config_signal

NAME = minishell
SRCS =	$(addsuffix .c, $(UTILS))\
		$(addsuffix .c, $(PARSER))\
		$(addsuffix .c, $(CALL))\
		$(addsuffix .c, $(SETUP))\
		main.c
		
OBJ_DIR = obj
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
