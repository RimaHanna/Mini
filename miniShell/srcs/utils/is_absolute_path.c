#include "minishell.h"

bool	is_absolute_path(t_statement *statement)
{
	if (is_instr(statement->argv[0], '/'))
		return (true);
	return (false);
}