#ifndef MINISHELL_H
#define MINISHELL_H


#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

#include "../libft/libft.h"

/*
	PREDEFINED MAN MACROS FOR FD
	STDIN_FILENO // return 0 // standard input stream
	STDERR_FILENO // return 2 // standard error stream
	STDOUT_FILENO // return 1 // standard output stream
*/


// DEFINE GLOBAL_STATUS ERROR
# define UNVALID_LINE 2

// DEFINE SYNTAX MESSAGE
# define UNCLOSED_QUOTE "minishell: unclosed quote"
# define SYNTAX_ERROR "minishell: syntax error"
# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token "
# define RED_SYT_ERR "minishell: syntax error near unexpected token `newline'"
# define ERROR_MESSAGE "minishell: no support for command-line arguments"

// DEFINE CONSTANT
# define QUOTES "\'\""
# define PIPE '|'
# define REDIRECTS "><"
# define OPERATORS "|<>" 


typedef enum e_operator
{
	NONE, // valeur 0
	OUT_RDR_OP, // > // valeur 1
	INP_RDR_OP, // < ...
	MUL_RDR_OP, // <<
	APP_RDR_OP, // >>
	PIPE_OP,
}				t_operator;

/* 	All functions regarding t_statemnent list are referring to parser */
/*	The t_statement structure holds information about a single shell 
command (its arguments, operator, and a pointer to the next command)*/
typedef struct s_statement
{
	int					argc;
	char				**argv;
	t_operator			operator;
	struct s_statement	*next;
}				t_statement;

typedef struct s_vlst {
	char			*var_name;
	char			*var_value;
	bool			is_exported;
	struct s_vlst	*next;
}				t_vlst;

/*	Data keeps a pointer to the head node in case of a need to call 
	exit_all() (fork or pipe error) 
	t_vlst: This structure represents a node in a linked list used to store 
	environment variables.
 */

typedef struct s_data
{
	char		**envp;
	t_vlst		*envp_lst;
	t_statement	*head;
}				t_data;

// PARSER
	// clean_parsed.c
void	free_argvs(char **argvs);
void	parse_lst_clean(t_statement **head);
void	clean_parsed(t_statement **statement_list, t_data *data);

	// expander.c
bool	single_dollar(char *input_at_i);
void	init_vars(size_t *i, size_t *size, bool *in_quotes, bool *in_dquotes);
size_t	exit_status_size(void);
size_t	expand_size(char *input_at_i, size_t *i, t_data *data);
int	expanded_size(char *input, t_data *data);
size_t	expand_exit_status(char *expanded_input_at_i, size_t *i);
char	*get_varvalue_fromvlst(char *var_name, t_data *data);
char	*get_fromvlst(char *var_name, t_vlst **head);
size_t	expand_variable(char *expanded_input_at_i, char *input,
	size_t *i, t_data *data);
char	*expander(char *line, t_data *data);


	// parser.c
size_t		get_argc(char **parsed);
bool		is_spaces(char c);
bool		streq(char *str1, char *str2);
t_operator	get_operator(char *operator);
t_statement	*p_new_node(int argc);
size_t		get_nb_statements(char *input);
size_t		get_token_len(char *input_at_i);
char		**parse_input(char *input);
t_statement	*parser(char *input);

   // remove_quotes.c
size_t		size_without_quotes(char *parsed);
char		*str_without_quotes(char *parsed);

	// string_trimming.c
char		*trim_whitespace_from_edges(char *line, char const *set);
char		*read_and_trim_lineofcommand(void);


	// syntax_check
bool		invalid_pipe_syntax(char *line);
bool		invalid_token_syntax(char *line);
bool		invalid_operator_syntax(char *line);

	// syntax_validation.c
int			unclosed_quote(char *str);
bool		unexpected_token(char token);
bool		string_has_operator(char *line);
bool		valid_lineofcommand(char *line, t_data *data);

//SETUP
	//config_signal.c
void		child_signals(int signum);
void		dismiss_signal(int signum);
void		config_signals(void);

	//init_and_setup_shell.c
char		**split_envp(char *env);
t_vlst		*v_new_node(char *var_name, char *var_value, bool is_exported);
t_vlst		*init_envp_lst(char **envp);
void		init_shell(char **envp, t_data *data, t_statement **statement_list);


// UTILS
long long	ft_digits(long long n);
char		*ft_lltoa(long long n);
char		*ft_strncpy(char *dest, const char *src, size_t n);
bool		is_instr(const char *str, char chr);

// MAIN
void		variable_lst_clean(t_vlst **head);
void		destroy(t_data *data);
void		exit_shell(int exit_status, t_data *data);
void		terminate_shell(t_data *data, char *msg, int exit_status);
void    	shell_loop();


#endif