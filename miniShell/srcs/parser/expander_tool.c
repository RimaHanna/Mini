#include "minishell.h"

/**
 * Determines if a dollar sign '$' should be treated as a variable or not.
 * It returns true if the dollar sign should be treated as a variable, which
 * occurs when it's followed by a space or double quotes (").
 * In shell scripts, a dollar sign typically indicates the start of a variable,
 * for example: $HOME (it replaces 'HOME' with the corresponding path). However,
 * if it immediately follows a double quote (") character, it's treated as a
 * literal character within a string, preventing variable expansion within that
 * string.
 *
 * @param {char *} input_at_i - The input character at the current position.
 * @returns {bool} True if the dollar sign should be treated as a variable,
 *                  otherwise false.
 */
bool	single_dollar(char *input_at_i)
{
	return ((!input_at_i[1]
			|| input_at_i[1] == ' '
			|| input_at_i[1] == '\"'));
}

/**
 * Retrieves the value associated with a given variable name from a linked list,
 * typically representing environment variables.
 *
 * @param var_name - A string representing the name of the variable whose value
 *                  you want to retrieve.
 * @param head     - A pointer to the head of the linked list containing the
 *                  environment variables.
 *
 * @return         - A pointer to the value associated with the specified
 *                  variable name. Returns NULL if the variable name is not 
 *                  found in the linked list.
 */
char	*get_fromvlst(char *var_name, t_vlst **head)
{
	t_vlst	*temp;

	temp = *head;
	while (temp != NULL)
	{
		if (streq(var_name, temp->var_name))
			return (temp->var_value);
		temp = temp->next;
	}
	return (NULL);
}

/**
 * Retrieves the value associated with a given variable name from the
 * environment variable linked list stored in the 't_data' structure.
 *
 * @param var_name - A string representing the name of the variable whose value
 *                  you want to retrieve.
 * @param data     - A pointer to the 't_data' structure containing the
 *                  environment variable linked list.
 *
 * @return         - A pointer to the value associated with the specified
 *                  variable name. Returns NULL if the variable name is not 
 *                  found in the linked list.
 */
char	*get_varvalue_fromvlst(char *var_name, t_data *data)
{
	char	*var_value;

	var_value = get_fromvlst(var_name, &data->envp_lst);
	free(var_name);
	return (var_value);
}

/**
 * Calculates the size of the expanded input by handling variable expansion,
 * identifying variable names following the '$' character, and expanding them 
 * by looking up their values in a list, typically representing environment 
 * variables.
 *
 * @param input_at_i The input string at the current index.
 * @param i Pointer to the current index within the input string.
 * @param data Pointer to the shell's data structure.
 *
 * @return The size of the expanded input or 0 if no expansion is needed.
 */
size_t	expand_size(char *input_at_i, size_t *i, t_data *data)
{
	size_t	var_size;
	char	*var_name;
	char	*var_value;

	*i += 1;
	if (single_dollar(input_at_i))
		return (1);
	var_size = 0;
	while (input_at_i[var_size + 1]
		&& input_at_i[var_size + 1] != ' '
		&& !is_instr(QUOTES, input_at_i[var_size + 1])
		&& input_at_i[var_size + 1] != '$')
				var_size++;
	if (var_size == 0)
		return (0);
	var_name = ft_substr(input_at_i, 1, var_size);
	var_value = get_fromvlst(var_name, &data->envp_lst);
	free(var_name);
	*i += var_size;
	if (!var_value)
		return (0);
	return (ft_strlen(var_value));
}


/**
 * Expands a variable reference in the input string and copies its value into  
 * the expanded input.
 * 
 * This function starts with 'i' pointing to the dollar sign ($) in the input 
 * string. It checks if the character immediately following the dollar sign is 
 * either the end of the input string or a space. If so, it treats the dollar  
 * sign as a literal character and writes it to 'expanded_input_at_i',  
 * returning 1 to indicate processing of one character.
 * 
 * If the character following the dollar sign is not a space or the end of the 
 * string, it means there is a variable to expand. The function calculates the  
 * size of the variable name by iterating through the characters until it 
 * encounters a space, double quote ("), another dollar sign ($), or the end
 * of the string.
 * 
 * It then extracts the variable name and looks up its value in the linked list  
 * of variables (envp_lst) using the 'get_varvalue_fromvlst' function.  
 * If a value is found for the variable, the function copies each character  
 * of the value to 'expanded_input_at_i', incrementing 'j' and 'k' accordingly.  
 * This effectively replaces the variable reference in the input string with 
 * its actual value.
 * 
 * @param expanded_input_at_i Pointer to the location in the expanded input  
 *                           where the variable value will be copied.
 * @param input               The input string.
 * @param i                   Pointer to the current position in the input
 * 							 string.
 * @param data                Pointer to the shell data structure containing 
 *                           environment variables.
 * 
 * @return                    The number of characters copied 
 * 							 to 'expanded_input_at_i'.
 */
size_t	expand_variable(char *expanded_input_at_i, char *input,
	size_t *i, t_data *data)
{
	char	*var_value;
	size_t	size;
	size_t	j;
	size_t	k;

	size = 0;
	j = 0;
	k = 0;
	*i += 1;
	if (!input[*i] || input[*i] == ' ' || input[*i] == '\"')
	{
		expanded_input_at_i[0] = '$';
		return (1);
	}
	while (input[*i + size] && input[*i + size] != ' '
		&& input[*i + size] != '\"' && !is_instr(QUOTES, input[*i + size])
		&& input[*i + size] != '$')
		size += 1;
	var_value = get_varvalue_fromvlst(ft_substr(input, *i, size), data);
	*i += size;
	if (!var_value)
		return (0);
	while (var_value[k])
		expanded_input_at_i[j++] = var_value[k++];
	return (j);
}
