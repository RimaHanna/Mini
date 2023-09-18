#include "minishell.h"

/**
 * Frees the memory allocated for an array of string arguments.
 *
 * @param {char **} arguments - The array of string arguments to free.
 */
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

/**
 * Cleans and deallocates memory for a linked list of statements.
 *
 * @param {t_statement **} head - Pointer to the head of the statement list.
 */
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

/**
 * Cleans and deallocates memory for a parsed statement list and data structure.
 *
 * @param {t_statement **} statement_list - Pointer to the statement list.
 * @param {t_data *} data - Pointer to the data structure.
 */
void	clean_parsed(t_statement **statement_list, t_data *data)
{
	parse_lst_clean(statement_list);
	*statement_list = NULL;
	data->head = NULL;
}