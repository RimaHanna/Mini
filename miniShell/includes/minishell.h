#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libft/libft.h"


/*
	PREDEFINED MAN MACROS FOR FD
	STDIN_FILENO // return 0 // standard input stream
	STDERR_FILENO // return 2 // standard error stream
	STDOUT_FILENO // return 1 // standard output stream
*/


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
# define OPERATORS "|<>" 


typedef enum e_operator
{
	NONE,
	OUT_RDR_OP, // >
	INP_RDR_OP, // <
	MUL_RDR_OP, // <<
	APP_RDR_OP, // >>
	PIPE_OP,
}				t_operator;

/* All functions regarding t_statemnent list are referring to parser */
typedef struct s_statement
{
	int					argc;
	char				**argv;
	t_operator			operator;
	struct s_statement	*next;
}				t_statement;

/* data keeps a pointer to the head node in
 case of a need to call panic() (fork or pipe error) */

typedef struct s_data
{
	char		**envp;
	t_statement	*head;
}				t_data;


// PARSER

    // remove_quotes.c
size_t	size_without_quotes(char *parsed);
char	*str_without_quotes(char *parsed);

	// invalid_syntax.c
int		unclosed_quote(char *str);
bool	unexpected_token(char token);
bool	invalid_syntax(char *line);
bool	string_has_operator(char *line);
bool	invalid_syntax_in_operator(char *line);
bool	valid_line(char *line);

	// parser.c
size_t	get_argc(char **parsed);
bool	is_spaces(char c);
bool	streq(char *str1, char *str2);
t_operator	get_operator(char *operator);
t_statement	*p_new_node(int argc);
size_t	get_nb_statements(char *input);
size_t	get_token_len(char *input_at_i);
char	**parse_input(char *input);
t_statement	*parser(char *input);




// UTILS
char	*ft_strncpy(char *dest, const char *src, size_t n);
bool	is_instr(const char *str, char chr);

// MAIN
char	*trim_free(char *line, char const *set);
char	*trim_line(void);
void	check_null_line(char *line);
void    shell_loop();


#endif