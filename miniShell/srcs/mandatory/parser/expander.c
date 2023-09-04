#include "minishell.h"

extern long long	g_last_exit_status;

/*
	This code appears to be essential for expanding variables and managing the 
	exit status within a minishell project, allowing users to work with 
	environment variables and special shell variables like $?
*/

void	init_vars(size_t *i, size_t *size, bool *in_quotes, bool *in_dquotes)
{
	*i = 0;
	*size = 0;
	*in_quotes = false;
	*in_dquotes = false;
}

/*
	single_dollar Function:
	This function checks if a dollar sign $ should be treated as a variable
	or not.
	It returns true if the dollar sign should be treated as a variable, i.e., if 
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
	This function calculates the size (number of digits) of the exit status 
	converted to a string.
*/
size_t	exit_status_size(void)
{
	char	*exit_status;
	size_t	size;

	exit_status = ft_lltoa(g_last_exit_status);
	size = ft_strlen(exit_status);
	free(exit_status);
	return (size);
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
				var_size += 1;
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
	This function calculates the total size of the expanded input by 
	iterating through the input string.
	It takes into account quotes and variables to calculate the final size.
*/
int	expanded_size(char *input, t_data *data)
{
	size_t	i;
	size_t	size;
	bool	in_quotes;
	bool	in_dquotes;

	init_vars(&i, &size, &in_quotes, &in_dquotes);
	while (input[i])
	{
		if (input[i] == '\"' && !in_quotes)
			in_dquotes = !in_dquotes;
		if (input[i] == '\'' && !in_dquotes)
			in_quotes = !in_quotes;
		if ((input[i] == '$' && input[i + 1] == '?') && !in_quotes)
		{
			size += exit_status_size() - 1;
			i += 1;
		}
		else if (input[i] == '$' && !in_quotes)
			size += expand_size(&(input[i]), &i, data) - 1;
		else
			i += 1;
		size += 1;
	}
	return (size);
}

/*
	This function expands the exit status ($?) by converting it to a string
	and copying it into the expanded input string.
*/
size_t	expand_exit_status(char *expanded_input_at_i, size_t *i)
{
	char	*exit_status;
	size_t	j;

	*i += 2;
	exit_status = ft_lltoa(g_last_exit_status);
	j = 0;
	while (exit_status[j])
	{
		expanded_input_at_i[j] = exit_status[j];
		j += 1;
	}
	free(exit_status);
	return (j);
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

/*
	This is the main function responsible for expanding an input command line.
	It iterates through the input, handling quotes and variables, and creates 
	an expanded input string.
	Example:
	Suppose you have the following input string:
	"Hello, $NAME! Your age is $AGE years old."
	Let's assume that:
	$NAME is assigned the value "John".
	$AGE is assigned the value 30.
	Expander function will perform variable expansion and return the following 
	expanded string:
	"Hello, John! Your age is 30 years old."
*/
char	*expander(char *input, t_data *data)
{
	size_t	i;
	size_t	j;
	bool	in_quotes;
	bool	in_dquotes;
	char	*expanded_input;

	init_vars(&i, &j, &in_quotes, &in_dquotes);
	expanded_input = malloc((expanded_size(input, data) + 1) * sizeof(char));
	while (input[i])
	{
		if (input[i] == '\"' && !in_quotes)
			in_dquotes = !in_dquotes;
		if (input[i] == '\'' && !in_dquotes)
			in_quotes = !in_quotes;
		if (input[i] == '$' && input[i + 1] == '?' && !in_quotes)
			j += expand_exit_status(&(expanded_input[j]), &i);
		else if (input[i] && input[i] == '$' && !in_quotes)
			j += expand_variable(&(expanded_input[j]), input, &i, data);
		else
			expanded_input[j++] = input[i++];
	}
	expanded_input[j] = '\0';
	free(input);
	return (expanded_input);
}
