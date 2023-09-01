#include "minishell.h"

void	free_argvs(char **arguments)
{
	size_t i;

	i = 0;
	if (!arguments)
		return ;
	while (arguments[i])
	{
		free(arguments[i]);
		arguments[i] = NULL;
		i++;
	}
	free(arguments);
	arguments = NULL;
}

void	parse_lst_clean(t_statement **head)
{
	t_statement *temp;
	t_statement *next_node;

	if (!head)
		return ;
	temp = *head;
	while (temp != NULL)
	{
		next_node = temp->next;
		free_argvs(temp->argv);
		free(temp);
		temp = next_node;
	}
	*head = NULL;
}

void	clean_parsed(t_statement **statement_list, t_data *data)
{
	parse_lst_clean(statement_list);
	*statement_list = NULL;
	data->head = NULL;
}