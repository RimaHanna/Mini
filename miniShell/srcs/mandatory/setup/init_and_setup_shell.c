#include "minishell.h"

/**
 * @brief Calculates the number of nodes in a linked list of t_statement.
 *
 * @param head - The pointer to the head of the linked list.
 * @return The number of nodes in the linked list.
 */
size_t	parser_lstsize(t_statement *head)
{
	t_statement	*temp;
	size_t		size;

	temp = head;
	size = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		size += 1;
	}
	return (size);
}

/*
 * @brief Splits an environment variable string into its name and value parts.
 * Malloc 3:
 * 	splitted[0]: Contains the variable name.
 * 	splitted[1]: Contains the variable value.
 * 	splitted[2]: Set to NULL to terminate the array.
 * @param env - The environment variable string in the format "name=value".
 * @return An array of strings containing the variable name and value.
*/
char	**split_envp(char *env)
{
	char	**splitted;
	size_t	indexof_equal;

	splitted = malloc(3 * sizeof(char *));
	indexof_equal = ft_strchr(env, '=') - env;
	splitted[0] = ft_substr(env, 0, indexof_equal);
	splitted[1] = ft_substr(env, indexof_equal + 1,
			ft_strlen(&env[indexof_equal]));
	splitted[2] = NULL;
	return (splitted);
}

/**
 * @brief Creates and initializes a new t_vlst node.
 *
 * @param var_name - The name of the environment variable.
 * @param var_value - The value of the environment variable.
 * @param is_exported - Indicates if the variable is exported.
 * @return A pointer to the newly created t_vlst node.
 */
t_vlst	*v_new_node(char *var_name, char *var_value, bool is_exported)
{
	t_vlst	*new_node;

	new_node = malloc(sizeof(t_vlst));
	new_node->var_name = var_name;
	new_node->var_value = var_value;
	new_node->is_exported = is_exported;
	new_node->next = NULL;
	return (new_node);
}

/**
 * Initializes a linked list of environment variables (t_vlst nodes) based on an
 * array of environment variable strings (envp).
 * 
 * This function parses each string in envp using the split_envp function to
 * extract the variable name, value, and whether it's exported. It creates and
 * links t_vlst nodes for each environment variable and returns a pointer to the
 * head of the linked list.
 * 
 * The use of envp[0] in the init_envp_lst function is to initialize the head of
 * the linked list. It assumes that the first environment variable (envp[0]) in
 * the envp array contains important initial environment information. 
 * Initializing the linked list with this first variable ensures that the linked
 * list has a starting point for further processing of environment variables.
 * 
 * @param envp An array of environment variable strings.
 * @return A pointer to the head of the linked list containing environment 
 * 		   variables.
 *         Returns NULL if envp is NULL.
 */
t_vlst	*init_envp_lst(char **envp)
{
	t_vlst	*head;
	t_vlst	*temp;
	char	**line;
	size_t	i;

	if (envp == NULL)
        return (NULL);
    // Initialize the head of the linked list
	line = split_envp(envp[0]);
	head = v_new_node(line[0], line[1], true);
	free(line);
	i = 1;
	temp = head;
    // Iterate through envp array to create and link nodes
	while (envp[i])
	{
	    // Split the current environment variable into name and value
		line = split_envp(envp[i]);
	    // Create a new node for the linked list with the name, value, and is_exported flag
		temp->next = v_new_node(line[0], line[1], true);
		free(line);
	    // Move to the next node in the linked list
		temp = temp->next;
		i += 1;
	}
//init_old_pwd(&head);
	return (head);
}

/**
 * @brief Initializes the shell by setting environment variables, 
 * initializing data structures, and configuring signal handlers.
 *
 * @param envp - The array of environment variable strings.
 * @param data - The t_data structure to store shell data.
 * @param statement_list - The pointer to the t_statement structure.
 */
void	init_shell(char **envp, t_data *data, t_statement **statement_list)
{
	data->envp = envp;
	data->envp_lst = init_envp_lst(envp);
	data->head = NULL;
	*statement_list = NULL;
	config_signals();
}