#include "minishell.h"

extern long long g_last_exit_status;

/**
 * Checks if a string is a valid environment variable name based on certain criteria.
 * Used to filter out invalid environment variable names.
 *
 * @param {char *} str - The string to be checked.
 *
 * @returns {bool} Returns true if the string is a valid environment variable name,
 *                 otherwise false.
 */
bool	is_valid_id(char *str)
{
	size_t	i;

	i = 0;
	if (streq(str, "="))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (is_digit(str[i]) || str[i] == '!' || str[i] == '@'
			|| str[i] == '{' || str[i] == '}' || str[i] == '-')
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Executes a statement only if it is built-in
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