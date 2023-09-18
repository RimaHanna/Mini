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
#include <fcntl.h>
#include <limits.h>

#include "../libft/libft.h"

/*
	PREDEFINED MAN MACROS FOR FD
	STDIN_FILENO // return 0 // standard input stream
	STDERR_FILENO // return 2 // standard error stream
	STDOUT_FILENO // return 1 // standard output stream
*/


// DEFINE GLOBAL_STATUS ERROR
# define SUCCESS 0
# define UNVALID_LINE 2

// DEFINE SYNTAX MESSAGE
# define NOT_FOUND NULL
# define UNCLOSED_QUOTE "minishell: unclosed quote"
# define SYNTAX_ERROR "minishell: syntax error"
# define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token "
# define RED_SYT_ERR "minishell: syntax error near unexpected token `newline'"
# define ERROR_MESSAGE "minishell: no support for command-line arguments"
# define PIPE_ERR "minishell: pipe() failed"
# define FORK_ERR "minishell: fork() failed"
# define OLDPWD_NOT_SET "minishell: cd: OLDPWD not set"
# define PATH_MAX	4096
# define EXIT_NON_NUMERIC_ARG "minishell: exit: numeric argument required" 
# define EXIT_TOO_MANY_ARGS "minishell: exit: too many arguments"
# define CD_TOO_MANY_ARGS "minishell: cd: too many arguments"


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

//COMMANDS
	//BUILTINS
	//cd
int			print_perror_msg(char *path);
void		update_pwd(t_data *data);
void		update_oldpwd(char *temp, t_data *data);
int			cd_oldpwd(char *temp, t_data *data);
int			cmd_cd(char *path, t_data *data);

	//echo
int			cmd_echo(t_statement *statement, bool has_n);

	//env
int			cmd_env(t_data *data);

	//exit
long long	ft_atoll(const char *str);
bool		is_all_digits_or_signals(char *str);
bool		fits_in_longlong(char *str);
void		cmd_exit(t_statement *s, t_data *data);

	//export
bool		is_onid(char *str, char c);
int			cmd_export(t_statement *statement, t_data *data);

	//pwd
int			cmd_pwd(void);

	//unset
int			unset_var(char *var_name, t_vlst **head);
int			cmd_unset(t_statement *s, t_vlst **head);
int			call_cmd_unset(t_statement *s, t_data *data);

	//cmd_binaries
void		cmd_not_found(char *cmd_name);
char		**get_paths(t_vlst *envp_lst);
char		*get_bin_path(char *cmd, char **paths);
void		exit_and_free_args(char **paths, char *cmd, int exit_status);
void		cmd_binaries(t_statement *statement, t_data *data);

	//exec_pipe
void		left_side(t_statement *nd, t_data *data, int pdes[2]);
void	 	right_side(t_statement *nd, t_data *data, int pdes[2]);
void		exec_pipe(t_statement *node, t_data *data);

	//exec_redirects
void		redirect_input_until(t_statement *node);
void		redirect_input(t_statement *node);
void		redirect_output(t_statement *node);
void		exec_redirects(t_statement *node, t_data *data);

// EXECUTION

	//buitin.c
bool		is_valid_id(char *str);
bool		builtin(t_statement *s, t_data *data);

	//call_cmd.c
int			call_cmd_cd(t_statement *s, t_data *data);
bool		get_exported_state(char *var_name, t_vlst **head);
int			save_user_vars(char *statement, t_vlst **head, bool to_export);
int			call_cmd_echo(t_statement *s);

	//ececute_lineofcommand.c
void		exec_cmd(t_statement *current_node, t_data *data);
void		exec_executables(t_statement *node, t_data *data);
void		execute_lineofcommand(t_statement *statement_list, t_data *data);

// PARSER
	// clean_parsed.c
void		free_argvs(char **argvs);
void		parse_lst_clean(t_statement **head);
void		clean_parsed(t_statement **statement_list, t_data *data);

	// expander_tool.c
bool		single_dollar(char *input_at_i);
char		*get_varvalue_fromvlst(char *var_name, t_data *data);
char		*get_fromvlst(char *var_name, t_vlst **head);
size_t		expand_size(char *input_at_i, size_t *i, t_data *data);
size_t		expand_variable(char *expanded_input_at_i, char *input,
	size_t *i, t_data *data);

	//expander.c
size_t		exit_status_size(void);
size_t		expand_exit_status(char *expanded_input_at_i, size_t *i);
void		init_vars(size_t *i, size_t *size, bool *in_quotes,
	bool *in_dquotes);
int			expanded_size(char *input, t_data *data);
char		*expander(char *line, t_data *data);

	//parser_tool.c
size_t		get_argc(char **parsed);
bool		is_spaces(char c);
bool		streq(char *str1, char *str2);
t_operator	get_operator(char *operator);

	// parser.c
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
size_t		parser_lstsize(t_statement *head);
char		**split_envp(char *env);
t_vlst		*v_new_node(char *var_name, char *var_value, bool is_exported);
t_vlst		*init_envp_lst(char **envp);
void		init_shell(char **envp, t_data *data, t_statement **statement_list);

	//init_old_pwd.c
void		init_old_pwd(t_vlst **head);

// UTILS
char		*ft_llinttoarray(long long n);
char		*ft_strncpy(char *dest, const char *src, size_t n);
bool		is_absolute_path(t_statement *statement);
bool		is_digit(int c);
bool		is_instr(const char *str, char chr);
char		*join_free(char *s1, char *s2);
//lists_manage.c
void		variable_lst_clean(t_vlst **head);
t_vlst		*v_lstlast(t_vlst *node);
void		v_lstadd_back(t_vlst **head, t_vlst *new);

// MAIN
void		destroy(t_data *data);
void		exit_shell(int exit_status, t_data *data);
void		terminate_shell(t_data *data, char *msg, int exit_status);
void    	shell_loop();

#endif