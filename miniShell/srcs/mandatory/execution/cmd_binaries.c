#include "minishell.h"

extern long long g_last_exit_status;

#define NOT_FOUND NULL

// UTILS
/*
Cette fonction concatène deux chaînes de caractères s1 et s2 et renvoie une 
nouvelle chaîne de caractères. Elle gère également la libération de la 
mémoire de s1
*/
char	*join_free(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*joined;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	joined = malloc((len_s1 + len_s2 + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	j = 0;
	while (j < len_s1)
		joined[i++] = s1[j++];
	j = 0;
	while (j < len_s2)
		joined[i++] = s2[j++];
	joined[i] = '\0';
	free(s1);
	return (joined);
}


/*
	Cette fonction prend la liste chaînée des variables d'environnement 
	envp_lst et recherche la variable d'environnement "PATH". Elle divise la 
	valeur de la variable "PATH" en une liste de chaînes de caractères 
	représentant les différents répertoires où le shell recherche les commandes.
*/
char	**get_paths(t_vlst *envp_lst)
{
	t_vlst	*temp;

	temp = envp_lst;
	while (!streq("PATH", temp->var_name))
	{
		temp = temp->next;
		if (temp == NULL)
			return (NULL);
	}
	return (ft_split(temp->var_value, ':'));
}


/*
	Cette fonction prend le nom de la commande cmd et la liste des chemins 
	paths où le shell doit rechercher la commande. Elle itère à travers les 
	chemins et essaie de trouver le chemin complet de la commande. Si la 
	commande est trouvée, elle renvoie le chemin complet, sinon elle 
	renvoie NULL.
	F_OK et X_OK are constants from the librairie unistd.h used with access
	function to check if the file or path exist.
*/
char	*get_bin_path(char *cmd, char **paths)
{
	size_t	i;
	char	*tmp;
	char	*bin_path;

	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		bin_path = join_free(tmp, cmd);
		if (access(bin_path, F_OK | X_OK) == 0)
			return (bin_path);
		free(bin_path);
		i += 1;
	}
	return (NULL);
}

/*
	Cette fonction est utilisée pour nettoyer la mémoire et quitter le 
	programme. Elle prend en compte la gestion des erreurs et définit le code 
	de sortie du shell (g_last_exit_status). Elle affiche également un message 
	d'erreur si la commande cmd a échoué.
*/
void	exit_and_free_args(char **paths, char *cmd, int exit_status)
{
	if (cmd)
		perror(cmd);
	free_argvs(paths);
	if (!WIFSIGNALED(g_last_exit_status))
		g_last_exit_status = exit_status;
	exit(g_last_exit_status);
}

/*
	It first checks if the command specified in statement is an absolute path. 
	If it is, it attempts to execute the command directly using execve. If the 
	execution is successful, the function returns.

	If the command is not an absolute path, it attempts to find the full path 
	to the command by searching through directories specified in the "PATH" 
	environment variable. It does this by calling the get_bin_path function.

	If the command is found in one of the directories, it attempts to execute 
	the command using execve. If the execution is successful, the function 
	returns.

	If the command is not found in any of the directories, it calls the 
	cmd_not_found function, indicating that the command is not recognized.

	After executing the command or handling errors, the function cleans up 
	memory and sets the shell's exit status code (g_last_exit_status) based 
	on the success or failure of the command execution.
*/
void	cmd_binaries(t_statement *statement, t_data *data)
{
	char	*bin_path;
	char	**paths;

	bin_path = statement->argv[0];
	paths = get_paths(data->envp_lst);
	if (is_absolute_path(statement))
	{
		if (execve(bin_path, statement->argv, data->envp) == -1)
			exit_and_free_args(paths, statement->argv[0], 127);
		exit_and_free_args(paths, NULL, EXIT_SUCCESS);
		return ;
	}
	bin_path = get_bin_path(statement->argv[0], paths);
	if (bin_path == NOT_FOUND)
	{
		cmd_not_found(statement->argv[0]);
		exit_and_free_args(paths, NULL, 127);
	}
	if (execve(bin_path, statement->argv, data->envp) == -1)
	{
		free(bin_path);
		exit_and_free_args(paths, statement->argv[0], 127);
	}
	free(bin_path);
	exit_and_free_args(paths, NULL, EXIT_SUCCESS);
}