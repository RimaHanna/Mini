#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libft/libft.h"


// DEFINE GLOBAL_STATUS ERROR
# define UNVALID_LINE 1

// DEFINE SYNTAX MESSAGE
# define UNCLOSED_QUOTE "minishell: unclosed quote"
# define SYNTAX_ERROR "minishell: syntax error"
# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token "

// DEFINE CONSTANT
# define QUOTES "\'\""
# define PIPE '|'
# define REDIRECTS "><"


// PARSER

    // remove_quotes
size_t	size_without_quotes(char *parsed);
char	*str_without_quotes(char *parsed);



// UTILS
char	*ft_strncpy(char *dest, const char *src, size_t n);
bool	is_instr(const char *str, char chr);


// MAIN
char	*trim_free(char *line, char const *set);
char	*trim_line(void);
void	check_null_line(char *line);
int	unclosed_quote(char *str);
bool	unexpected_token(char token);
bool	invalid_syntax(char *line);
bool	valid_line(char *line);
void    shell_loop();


#endif