#include "minishell.h"


/**
 * @description Executes a statement only if it is built-in
 * Returns (true) if the statement is a built-in command and was executed,
 * (false) otherwise
 * @param {t_statement *} s, pointer to statement
 * @param {t_data *} data, pointer to the entire command line
 * @returns {bool}
*/
// Suite FILE: call_cmd.c
bool	builtin(t_statement *s, t_data *data)
{
	if (streq(s->argv[0], "exit"))
		cmd_exit(s, data);
	else if (streq(s->argv[0], "unset"))
		g_last_exit_status = call_cmd_unset(s, data);
	else if (streq(s->argv[0], "export"))
		g_last_exit_status = cmd_export(s, data);
	else if (streq(s->argv[0], "cd"))
		g_last_exit_status = call_cmd_cd(s, data);
	else if (ft_strchr(s->argv[0], '=') && is_valid_id(s->argv[0]))
		g_last_exit_status = save_user_vars(s->argv[0],
				&data->envp_lst, false);
	else if (streq(s->argv[0], "echo"))
		g_last_exit_status = call_cmd_echo(s);
	else if (streq(s->argv[0], "pwd"))
		g_last_exit_status = cmd_pwd();
	else if (streq(s->argv[0], "env"))
		g_last_exit_status = cmd_env(data);
	else
		return (false);
	return (true);
}

/**
 * @description Checks if a statement is a built-in
 * This function does not execute the statement
 * @param {t_statement *} s, pointer to statement
 * @param {t_data *} data, pointer to the entire command line
 * @returns {bool}
 * @author Rima
 * @date 20230909
 * @creation
*/
// Suite FILE: call_cmd.c
bool	is_builtin(t_statement *s)
{
	if (streq(s->argv[0], "exit"))
		return (true);
	else if (streq(s->argv[0], "unset"))
		return (true);
	else if (streq(s->argv[0], "export"))
		return (true);
	else if (streq(s->argv[0], "cd"))
		return (true);
	else if (ft_strchr(s->argv[0], '=') && is_valid_id(s->argv[0]))
		return (true);
	else if (streq(s->argv[0], "echo"))
		return (true);
	else if (streq(s->argv[0], "pwd"))
		return (true);
	else if (streq(s->argv[0], "env"))
		return (true);
	else
		return (false);
}