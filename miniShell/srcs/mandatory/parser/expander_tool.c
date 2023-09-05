#include "minishell.h"

/*
	single_dollar Function:
	This function checks if a dollar sign $ should be treated as a variable
	or not.
	It returns true if the dollar sign should be treated as a variable, if 
	it's followed by a space or double quotes (").
	A dollar sign ($) in shell scripts typically indicates the start of a 
	variable ex: $HOME (it replace home with the path). However, if it 
	immediately follows a double quote ("), it's treated as a literal character 
	within a string, preventing variable expansion within that string.
*/
bool	single_dollar(char *input_at_i)
{
	return ((!input_at_i[1]
			|| input_at_i[1] == ' '
			|| input_at_i[1] == '\"'));
}


/*
	These functions retrieve the value associated with a given variable name 
	from a linked list (likely representing environment variables)
	var_name: A string representing the name of the variable whose value 
	you want to retrieve.
	The function takes the var_name as input, which is the name of the variable 
	you want to find the value for.
	It iterates through the linked list (envp_lst) to find a node where the 
	var_name matches the var_name stored in the list node (temp->var_name).
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

char	*get_varvalue_fromvlst(char *var_name, t_data *data)
{
	char	*var_value;

	var_value = get_fromvlst(var_name, &data->envp_lst);
	free(var_name);
	return (var_value);
}

/*
	This function calculates the size of the expanded input by handling 
	variable expansion, taking care of different cases.
	It identifies variable names following the $ character and expands
	them by looking up their values in a list (likely representing environment 
	variables).
	ft_substr takes an input string s, extracts a substring starting from 
	the specified start index with a maximum length of len, and returns a 
	new dynamically allocated string containing the extracted substring
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


/*
	This function handles the expansion of a variable and copies its value into 
	the expanded input.
	The function begins by incrementing i to move past the dollar sign ($) 
	that triggered the variable expansion. So it means that the function starts 
	with i pointing to the dollar sign ($) in the input string
	The function checks if the character immediately following the dollar 
	sign is either the end of the input string or a space. If so, it means 
	that the dollar sign should be treated as a literal character, not the 
	start of a variable. In this case, it writes the dollar sign as is to 
	expanded_input_at_i and returns 1 to indicate that one character has 
	been processed.
	If the character following the dollar sign is not a space or the end of the 
	string, it means there is a variable to expand.
	The function calculates the size of the variable name by iterating through 
	the characters until it encounters a space, double quote ("), another 
	dollar sign ($), or the end of the string.
	It then extracts the variable name and looks up its value in the linked 
	list of variables (envp_lst) using the get_varvalue_fromvlst function.
	If a value is found for the variable, the function copies each character 
	of the value to expanded_input_at_i, incrementing j and k accordingly.
	This effectively replaces the variable reference in the input string with 
	its actual value.
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
