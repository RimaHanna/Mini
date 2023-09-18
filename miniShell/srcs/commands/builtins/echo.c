#include "minishell.h"

static void	print(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			i++;
			continue ;
		}
		ft_putchar_fd(str[i], STDOUT_FILENO);
		i++;
	}
}

int	cmd_echo(t_statement *statement, bool has_n)
{
	int		i;

	i = 1;
	if (has_n)
		i++;
	while (statement->argv[i] && i != statement->argc)
	{
		print(statement->argv[i]);
		if (!statement->argv[i + 1] && statement->operator != INP_RDR_OP)
			break ;
		ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	return (EXIT_SUCCESS);
}