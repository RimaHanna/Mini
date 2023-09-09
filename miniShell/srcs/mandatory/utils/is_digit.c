#include "minishell.h"


bool	is_digit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (true);
	return (false);
}