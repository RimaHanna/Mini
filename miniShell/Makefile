CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
LINK = -I./includes
VPATH = srcs srcs/mandatory\
		srcs/mandatory/parser srcs/mandatory/utils srcs/mandatory/call\
		srcs/mandatory/setup srcs/mandatory/execution
RM = rm -rf
LIBFT = ./libft/libft.a

UTILS = ft_strncpy is_instr ft_llinttoarray
PARSER = remove_quotes syntax_validation parser clean_parsed expander\
			string_trimming syntax_check expander_tool
SETUP = init_and_setup_shell config_signal init_old_pwd
EXECUTION = execute_lineofcommand call_cmd cmd_binaries builtin\

NAME = minishell
SRCS =	$(addsuffix .c, $(UTILS))\
		$(addsuffix .c, $(PARSER))\
		$(addsuffix .c, $(CALL))\
		$(addsuffix .c, $(SETUP))\
		$(addsuffix .c, $(EXECUTION))\
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
