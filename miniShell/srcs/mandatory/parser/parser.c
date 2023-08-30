#include "minishell.h"

/* 
	get_argc: Calculates the number of elements (arguments) in an array of 
	strings.
*/
size_t	get_argc(char **parsed)
{
	size_t	i;

	i = 0;
	while (parsed[i])
		i += 1;
	return (i);
}

bool	is_spaces(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (true);
	return (false);
}

/*
	streq: Compares two strings and returns true if they are equal.
*/
bool	streq(char *str1, char *str2)
{
	size_t	i;

	if ((str1 && !str2) || (!str1 && str2))
		return (false);
	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (false);
		i += 1;
	}
	return (true);
}

/*
	get_operator: Returns the corresponding operator enum based on the input
	string. Also frees the input string.
*/
t_operator	get_operator(char *operator)
{
	t_operator	op;

	if (!operator)
		op = NONE;
	else if (streq(operator, "|"))
		op = PIPE;
	else if (streq(operator, ">>"))
		op = APP_RDR_OP;
	else if (streq(operator, ">"))
		op = OUT_RDR_OP;
	else if (streq(operator, "<<"))
		op = MUL_RDR_OP;
	else if (streq(operator, "<"))
		op = INP_RDR_OP;
	else
		op = NONE;
	free(operator);
	return (op);
}

/*
	p_new_node: Creates and initializes a new t_statement node.

*/
t_statement	*p_new_node(int argc)
{
	t_statement	*new_node;

	new_node = malloc(sizeof(t_statement));
	new_node->argc = argc;
	new_node->argv = malloc((argc + 1) * sizeof(char *));
	new_node->operator = NONE;
	new_node->next = NULL;
	return (new_node);
}

/*
	Function get_nr_statements:
	Calculates the number of statements (commands) based on input text.
	Considers operators, quotes, and spaces to determine where statements end.
	Handles cases where quotes are used to group characters.
*/
size_t	get_nr_statements(char *input)
{
	size_t	count;
	bool	flag;
	bool	quotes;

	count = 0;
	flag = false;
	quotes = false;
	while (*input)
	{
		if (is_instr(OPERATORS, *input))
			count += 1;
		if (is_instr(QUOTES, *input) && *input == *(input + 1))
			input += 1;
		else if (is_instr(QUOTES, *input))
			quotes = !quotes;
		if (*input != ' ' && !is_instr(OPERATORS, *input) && !flag && !quotes)
		{
			flag = true;
			count += 1;
		}
		else if (*input == ' ' || is_instr(OPERATORS, *input))
			flag = false;
		input += 1;
	}
	return (count);
}


/*
	Function get_token_len:
	Calculates the length of a token (argument or operator) starting
	from a given position.
	Takes care of handling operators and spaces, as well as quoted substrings.
*/
size_t	get_token_len(char *input_at_i)
{
	size_t	i;
	char	quotes;

	i = 0;
	if (is_instr(OPERATORS, input_at_i[i]))
	{
		if (input_at_i[i] == input_at_i[i + 1])
			return (2);
		return (1);
	}
	while (input_at_i[i]
		&& !is_spaces(input_at_i[i])
		&& !is_instr(OPERATORS, input_at_i[i]))
	{
		if (is_instr(QUOTES, input_at_i[i]))
		{
			quotes = input_at_i[i++];
			while (input_at_i[i] && input_at_i[i] != quotes)
				i += 1;
		}
		i += 1;
	}
	return (i);
}

/*
	Function parse_input:
	Splits the input into an array of strings (tokens) representing statements 
	and operators.
	Uses the get_nr_statements and get_token_len functions to determine the 
	length of each token.
	Handles quoted substrings correctly.
*/

char	**parse_input(char *input)
{
	size_t		i;
	size_t		k;
	char		**parsed;
	size_t		len;
	size_t		j;

	i = 0;
	k = 0;
	parsed = malloc((get_nr_statements(input) + 1) * sizeof(char *));
	while (input[i])
	{
		len = get_token_len(&input[i]);
		if (!len)
		{
			i += 1;
			continue ;
		}
		parsed[k] = malloc((len + 1) * sizeof(char));
		j = 0;
		while (input[i] && j < len)
			parsed[k][j++] = input[i++];
		parsed[k++][j] = '\0';
	}
	parsed[k] = NULL;
	return (parsed);
}

/*
	Function parser:
	The main parser function that processes the input text to create a linked 
	list of t_statement nodes.
	Calls parse_input to tokenize the input.
	Creates a new node using p_new_node and assigns the head of the linked 
	list (head) to it.
	Iterates through the parsed tokens:
	Fills the argv array of the current node with arguments (without quotes) 
	until an operator is encountered.
	Sets the last element of argv to NULL.
	If there are more tokens, assigns the operator and creates a new node for 
	the next statement.
	Sets the next of the last node to NULL.
	Frees the parsed array.
	Returns the head of the linked list.
*/
t_statement	*parser(char *input)
{
	char		**parsed;
	t_statement	*temp;
	t_statement	*head;
	size_t		idx[2];

	parsed = parse_input(input);
	free(input);
	temp = p_new_node(get_argc(&parsed[0]));
	head = temp;
	idx[0] = 0;
	while (parsed[idx[0]])
	{
		idx[1] = 0;
		while (parsed[idx[0]] && !is_instr(OPERATORS, parsed[idx[0]][0]))
			temp->argv[idx[1]++] = str_without_quotes(parsed[idx[0]++]);
		temp->argv[idx[1]] = NULL;
		if (!parsed[idx[0]])
			break ;
		temp->operator = get_operator(parsed[idx[0]++]);
		temp->next = p_new_node(get_argc(&parsed[idx[1]]));
		temp = temp->next;
	}
	temp->next = NULL;
	free(parsed);
	return (head);
}
