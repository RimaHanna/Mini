#include "minishell.h"

static inline int	cd_too_many_args(void)
{
	ft_putendl_fd(CD_TOO_MANY_ARGS, STDERR_FILENO);
	return (EXIT_FAILURE);
}

int	call_cmd_cd(t_statement *s, t_data *data)
{
	if (s->argc > 2)
		return (cd_too_many_args());
	else
		return (cmd_cd(s->argv[1], data));
}

bool	get_exported_state(char *var_name, t_vlst **head)
{
	t_vlst	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (streq(var_name, temp->var_name))
			return (temp->is_exported);
		temp = temp->next;
	}
	return (false);
}

int	save_user_vars(char *statement, t_vlst **head, bool to_export)
{
	char	**line;

	line = split_envp(statement);
	if (get_exported_state(line[0], head) && !to_export)
		to_export = true;
	unset_var(line[0], head);
	v_lstadd_back(head, v_new_node(line[0], line[1], to_export));
	free(line);
	return (EXIT_SUCCESS);
}

int	call_cmd_echo(t_statement *s)
{
	t_statement	*temp;
	bool		has_n;

	temp = s;
	has_n = false;
	if (s->argc >= 2)
		has_n = streq(s->argv[1], "-n");
	cmd_echo(temp, has_n);
	temp = temp->next;
	while (temp != NULL && temp->argc > 2)
	{
		cmd_echo(temp, false);
		if (temp->operator == PIPE)
			break ;
		temp = temp->next;
	}
	if (!has_n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}