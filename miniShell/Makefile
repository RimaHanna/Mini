CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
LINK = -I./includes
VPATH = srcs srcs/commands srcs/execution srcs/parser srcs/setup srcs/utils\
		srcs/commands/builtins
RM = rm -rf
LIBFT = ./libft/libft.a

COMMANDS = cmd_binaries exec_pipe exec_redirects
BUILTINS = cd echo env exit export pwd unset
EXECUTION = builtin call_cmd execute_lineofcommand
PARSER = clean_parsed expander_tool expander parser remove_quotes\
			string_trimming syntax_check syntax_validation parser_tool
SETUP = config_signal init_and_setup_shell init_old_pwd
UTILS = ft_llinttoarray ft_strncpy is_digit is_instr join_free lists_manage\
			is_absolute_path

NAME = minishell
SRCS =	$(addsuffix .c, $(COMMANDS))\
		$(addsuffix .c, $(BUILTINS))\
		$(addsuffix .c, $(EXECUTION))\
		$(addsuffix .c, $(PARSER))\
		$(addsuffix .c, $(SETUP))\
		$(addsuffix .c, $(UTILS))\
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
