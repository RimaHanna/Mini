#include "minishell.h"

/**
 * @brief Initialize the value of the 'OLDPWD' environment variable.
 * This function unsets the 'OLDPWD' variable, creates a new one with the value
 * of the user's home directory, and saves it.
 *
 * @param head A pointer to the head of the environment variable linked list.
 */

void	init_old_pwd(t_vlst **head)
{
	char	*temp;

	unset_var("OLDPWD", head);
	temp = ft_strjoin("OLDPWD=", getenv("HOME"));
	save_user_vars(temp, head, true);
	free(temp);
}
