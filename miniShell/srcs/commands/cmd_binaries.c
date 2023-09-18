#include "minishell.h"

extern long long g_last_exit_status;

/**
 * Displays an error message indicating that a command was not found and 
 * prints the command name to the standard error.
 *
 * @param {char *} cmd_name - The name of the command that was not found.
 */
void	cmd_not_found(char *cmd_name)
{
	ft_putstr_fd(cmd_name, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

/**
 * This function takes the linked list of environment variables envp_lst
 * and looks for the "PATH" environment variable. It splits at ":" the value of 
 * the "PATH" variable into a list of strings representing different directories
 * where the shell searches for commands.
 *
 * @param envp_lst A pointer to the linked list of environment variables.
 * @return An array of strings representing directories in the "PATH" variable,
 *         or NULL if "PATH" is not found in the environment variables.
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

/**
 * Finds the full path of a command 'cmd' within a list of 'paths'.
 * Iterates through 'paths' and attempts to locate the complete path
 * of the command. If found, it returns the full path; otherwise, it returns 
 * NULL.
 * 
 * @param cmd - The name of the command to locate.
 * @param paths - A list of directories to search for the command.
 * 
 * @return A pointer to the full path of 'cmd' if found; otherwise, NULL.
 * 
 * Note: F_OK and X_OK are constants from the unistd.h library used with
 * the access() function to check if the file or path exists.
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

/**
 * Cleans up memory and exits the program with error handling.
 *
 * This function is used to perform memory cleanup and exit the program.
 * It handles errors and sets the shell's exit code (g_last_exit_status).
 * Additionally, it displays an error message if the command 'cmd' fails.
 *
 * @param paths - Array of strings representing paths to release memory for.
 * @param cmd - Command that may have failed, used for error message.
 * @param exit_status - Exit status code to be set for the shell.
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

/**
 * Executes the specified command in a child process.
 *
 * This function first checks if the command specified in the 'statement' is an
 * absolute path. If it is, it attempts to execute the command directly using
 * 'execve'. If the execution is successful, the function returns.
 *
 * 'execve': When 'execve' is called, the current process is replaced entirely
 * by the new program specified in 'pathname'. This means that the new program
 * starts executing from its main function or entry point, and the old program's
 * code and data are discarded. 'execve' returns only if an error occurs. If the
 * specified executable file does not exist or is not executable, or if there
 * are other issues with the arguments, 'execve' will return an error code,
 * allowing the calling process to handle the error.
 *
 * If the command is not an absolute path, it attempts to find the full path to
 * the command by searching through directories specified in the "PATH"
 * environment variable. It does this by calling the 'get_bin_path' function.
 *
 * If the command is found in one of the directories, it attempts to execute the
 * command using 'execve'. If the execution is successful, the function returns.
 *
 * If the command is not found in any of the directories, it calls the
 * 'cmd_not_found' function, indicating that the command is not recognized.
 *
 * After executing the command or handling errors, the function cleans up memory
 * and sets the shell's exit status code ('g_last_exit_status') based on the
 * success or failure of the command execution.
 *
 * @param statement The statement containing the command and its arguments.
 * @param data The shell's data structure, including environment variables.
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