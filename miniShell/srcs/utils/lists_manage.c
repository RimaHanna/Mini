#include "minishell.h"

/**
 * @brief Clean the variable list.
 * 
 * This function is responsible for cleaning up a linked list of variables.
 * It iterates through the list and frees the memory associated with each node.
 * Finally, it sets the head of the list to NULL.
 * 
 * @param head - A pointer to a pointer to the head of the variable list.
 * @return void
 */
void	variable_lst_clean(t_vlst **head)
{
	t_vlst	*temp;
	t_vlst	*next_node;

	if (!head)
		return ;
	temp = *head;
	while (temp != NULL)
	{
		next_node = temp->next;
		free(temp->var_name);
		free(temp->var_value);
		free(temp);
		temp = next_node;
	}
	*head = NULL;
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