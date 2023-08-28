#include <minishell.h>

/*
    Function checking is the character exist in the string
    return true if the character exist in the string
    return false if the character doesn't exist in the string
*/
bool	is_instr(const char *str, char chr)
{
	int i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (chr == str[i])
	    	return (true);
		i++;
	}
	return (false);
}