#include "minishell.h"


//cmd_exit: WITH RANIA

//cmd_unset
int	call_cmd_unset(t_statement *s, t_data *data)
{
	if (s->argc == 1)
		return (EXIT_SUCCESS);
	return (cmd_unset(s, &data->envp_lst));
}

//cmd_export: WITH RANIA

int	call_cmd_cd(t_statement *s, t_data *data)
{
	if (s->argc > 2)
		return (cd_too_many_args());
	else
		return (cmd_cd(s->argv[1], data));
}

//cd_too_many_args: WITH RANIA
//cmd_cd: WITH RANIA


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
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

t_vlst	*v_lstlast(t_vlst *node)
{
	while (node)
	{
		if (!node->next)
			break ;
		node = node->next;
	}
	return (node);
}

void	v_lstadd_back(t_vlst **head, t_vlst *new)
{
	t_vlst	*temp;

	if (head)
	{
		if (!*head)
			*head = new;
		else
		{
			temp = v_lstlast(*(head));
			temp->next = new;
		}
	}
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

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&7


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
// cmd_echo: WITH RANIA

// cmd_pwd: WITH RANIA

// cmd_env: WITH RANIA