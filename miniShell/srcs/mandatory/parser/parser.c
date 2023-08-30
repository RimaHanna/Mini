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
		op = PIPE_OP;
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
	Function get_nb_statements:
	Calculates the number of statements (commands) based on input text.
	Considers operators, quotes, and spaces to determine where statements end.
	Handles cases where quotes are used to group characters.
*/
size_t get_nb_statements(char *input)
{
    size_t count;   // Stores the number of statements
    bool flag;      // Indicates whether a statement is being processed
    bool quotes;    // Indicates whether quotes are currently active

    count = 0;      // Initialize the count to zero
    flag = false;   // Initialize the flag to false
    quotes = false; // Initialize the quotes flag to false

    while (*input) // Loop through each character in the input string
    {
        // If the current character is an operator, increment the count
        if (is_instr(OPERATORS, *input))
            count += 1;


        // Check for double quotes and skip the next character if they match
        if (is_instr(QUOTES, *input) && *input == *(input + 1))
            input += 1;
        // Toggle the quotes flag if a single quote is encountered
        else if (is_instr(QUOTES, *input))
            quotes = !quotes;

        // If the current character is not a space, not an operator, not inside quotes,
        // and a statement is not already being processed, mark the start of a new statement
        if (*input != ' ' && !is_instr(OPERATORS, *input) && !flag && !quotes)
        {
            flag = true;    // Set the flag to indicate that a statement is being processed
            count += 1;     // Increment the count for the new statement
        }
        // If the current character is a space or an operator, reset the flag
        else if (*input == ' ' || is_instr(OPERATORS, *input))
            flag = false;

        input += 1; // Move to the next character in the input string
    }\
//printf("get_nb_statments count %ld\n", count);
    return (count); // Return the final count of statements
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
	Uses the get_br_statements and get_token_len functions to determine the 
	length of each token.
	Handles quoted substrings correctly.
*/
char	**parse_input(char *input)
{
	size_t		i;
	size_t		k;
	size_t		len;
	size_t		j;
	char		**parsed;

	i = 0;
	k = 0;
	parsed = malloc((get_nb_statements(input) + 1) * sizeof(char *));
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
	size_t		idx[2]; // An array to store two index, instead of divising 
						// into i and j and have 2 lines.

    // Tokenize the input command.
	parsed = parse_input(input);
	free(input);

    // Create a new node for the linked list and assign it as the head.
	temp = p_new_node(get_argc(&parsed[0]));
	head = temp;

    // idx[0] stores the current position in the parsed array.
	idx[0] = 0;
	while (parsed[idx[0]])
	{
        // idx[1] will store the index for filling argv of the current statement.
		idx[1] = 0;
		while (parsed[idx[0]] && !is_instr(OPERATORS, parsed[idx[0]][0]))
		{
			temp->argv[idx[1]++] = str_without_quotes(parsed[idx[0]/*++*/]);
    printf("Adding argument to argv: %s\n", temp->argv[idx[1] - 1]);
		idx[0]++;
		}
        // Set the last element of argv to NULL.
		temp->argv[idx[1]] = NULL;
		if (!parsed[idx[0]])
			break ;

        // Set the operator for the current statement.
		temp->operator = get_operator(parsed[idx[0]++]);
    printf("Current statement operator: %d\n", temp->operator);
        
		// Create a new node for the next statement and assign it to temp->next.
		temp->next = p_new_node(get_argc(&parsed[idx[1]]));
		temp = temp->next;
// Print the result of temp->next
if (temp) 
    printf("Next node has %d arguments.\n", temp->argc);
else
    printf("No more nodes after this one.\n");
	}
	temp->next = NULL;
	free(parsed);
	return (head);
}


