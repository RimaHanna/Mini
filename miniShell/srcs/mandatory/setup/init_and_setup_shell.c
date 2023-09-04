#include "minishell.h"


/*
	This function takes a string env representing an environment variable in 
	the format "name=value".
	Malloc 3:
		splitted[0]: Contains the variable name.
		splitted[1]: Contains the variable value.
		splitted[2]: Set to NULL to terminate the array.
	Notes:
	ft_strchr locates the first occurrence of a character c in a string s.
	ft_substr  create a new substring from a given string s, starting at 
	position start and having a maximum length of len.
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

/*
	This function creates and initializes a new t_vlst node
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

/*
	This function initializes a linked list of environment 
	variables (t_vlst nodes) based on an array of environment variable strings 
	envp.
	It parses each string in envp using the split_envp function to extract the 
	variable name, value, and whether it's exported.
	It creates and links t_vlst nodes for each environment variable and returns 
	a pointer to the head of the linked list.
	The use of envp[0] in the init_envp_lst function is to initialize the head 
	of the linked list. It assumes that the first environment variable (envp[0])
	in the envp array contains important initial environment information. 
	Initializing the linked list with this first variable ensures that the 
	linked list has a starting point for further processing of environment
	variables.
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
//	init_oldpwd(&head);
	return (head);
}

void	setup_shell(char **envp, t_data *data, t_statement **statement_list)
{
	data->envp = envp;
	data->envp_lst = init_envp_lst(envp);
	data->head = NULL;
	*statement_list = NULL;
	config_signals();
}