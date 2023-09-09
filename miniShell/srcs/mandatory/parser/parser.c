#include "minishell.h"

/*
	This code is responsible for tokenizing and parsing user input into a 
	linked list of statements, where each statement represents a command 
	with arguments and operators. 
	The code relies on the sequence of the input string and the presence of 
	operators to identify commands and their arguments.
	
	Here's how it typically works:

	1- The code starts parsing the input string from left to right.
	2- It identifies and separates commands and their arguments based on the 
	presence of operators such as |, <, >, <<, and >>.
	3- When it encounters an operator, it marks the end of the current command 
	and starts parsing the next one.
	4- It assumes that the first token in each command sequence is the command 
	itself, and the subsequent tokens are its arguments.
	5- The type of operator (e.g., pipe |, input redirection <, 
	output redirection >, etc.) is associated with the command to 
	indicate how commands are connected.
*/
/*
	get_argc, is_spaces, streq, get_operator, p_new_node, get_nb_statements, 
	get_token_len, and parse_input. These functions are used to perform tasks 
	like counting arguments, comparing strings, and parsing the input into 
	tokens.
*/

/* 
	get_argc: Calculates the number of elements (arguments) in an array of 
	strings.
*/
/*
// FUNCTION DON"T GET THE ARGC DEVISED BY STATEMENT
size_t	get_argc(char **parsed)
{
	size_t	i;

	i = 0;
	while (parsed[i])
		i++;
//printf("l:41 get_argc number which is number of arguments = [%ld]\n", i);
	return (i);
}
*/

size_t	get_argc(char **parsed)
{
	size_t	i;

	i = 0;
	while ((parsed[i]) && ((ft_strlen(parsed[i]) != 1) 
			|| !is_instr(OPERATORS, parsed[i][0])))
		i++;
	return i;
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
	Considers OPERATORS "|<>" , QUOTES "\'\"" , and spaces to determine
	where statements end.
	Handles cases where quotes are used to group characters.
	EXAMPLE:
	get_nb_statments("ls -l | cat -e")
	return result 2 (1 until the operator and one until the NULL)
	But in order that it put the right result it should be between quote
*/
size_t get_nb_statements(char *input)
{
    size_t count;   // Stores the number of statements
    bool flag;      // Indicates whether a statement is being processed
    bool quotes;    // Indicates whether quotes are currently active

    count = 0;      // Initialize the count to zero
    flag = false;   // Initialize the flag to false
    quotes = false; // Initialize the quotes flag to false
//printf("l:134 get_nb_statements the input is [%s]\n", input);
    while (*input) // Loop through each character in the input string
    {
//printf("l:137 get_nb_statement the character is [%c]\n", *input);
        // If the current character is an operator, increment the count
        if (is_instr(OPERATORS, *input))
            count++;

        // Check for double quotes and skip the next character if they match
        if (is_instr(QUOTES, *input) && *input == *(input + 1))
            input++;
        // Toggle the quotes flag if a single quote is encountered
        else if (is_instr(QUOTES, *input))
            quotes = !quotes;

        // If the current character is not a space, not an operator, not inside quotes,
        // and a statement is not already being processed, mark the start of a new statement
        if (*input != ' ' && !is_instr(OPERATORS, *input) && !flag && !quotes)
        {
            flag = true;    // Set the flag to indicate that a statement is being processed
            count++;     // Increment the count for the new statement
        }
        // If the current character is a space or an operator, reset the flag
        else if (*input == ' ' || is_instr(OPERATORS, *input))
            flag = false;

        input++; // Move to the next character in the input string
    }
//printf("l:158 get_nb_statments [%ld]\n", count);
    return (count); // Return the final count of statements
}

/*
	Function get_token_len:
	Calculates the length of a token (argument or operator) starting
	from a given position.
	Takes care of handling operators and spaces, as well as quoted substrings.
*/
size_t get_token_len(char *input_at_i)
{
    size_t i;        // Index variable
    char quotes;     // Character to track the opening quote type

    i = 0;           // Initialize the index to zero
    if (is_instr(OPERATORS, input_at_i[i])) // Check if the character is an operator
    {
        if (input_at_i[i] == input_at_i[i + 1]) // If it's a double operator
            return 2; // Return a length of 2
        return 1; // If it's a single operator, return a length of 1
    }
    
    while (input_at_i[i] && !is_spaces(input_at_i[i]) && !is_instr(OPERATORS, input_at_i[i]))
    {
        // Loop while the current character exists, is not a space, and is not an operator
        if (is_instr(QUOTES, input_at_i[i]))
        {
            quotes = input_at_i[i++]; // Store the opening quote character
            while (input_at_i[i] && input_at_i[i] != quotes)
                i++; // Increment i until the closing quote character is found
        }
        i++; // Move to the next character
    }
//printf("l:194 get_token_len = [%ld] at letter: [%c]\n", i, *input_at_i);
    return i; // Return the length of the token
}


/*
	Function parse_input:
	Splits the input into an array of strings (tokens) representing statements 
	and operators.
	Uses the get_nb_statements and get_token_len functions to determine the 
	length of each token.
	Handles quoted substrings correctly.
*/
char **parse_input(char *input)
{
    size_t i;       // Index for iterating through input
    size_t k;       // Index for iterating through parsed array
    size_t len;     // Length of the current token
    size_t j;       // Index for copying characters within a token
    char **parsed;  // Array to store parsed tokens

    i = 0;          // Initialize index for input to 0
    k = 0;          // Initialize index for parsed array to 0
    // Allocate memory for the parsed array to hold the maximum possible number of tokens
    parsed = malloc((get_nb_statements(input) + 1) * sizeof(char *));
    while (input[i])
    {
        // Get the length of the current token starting from input[i]
        len = get_token_len(&input[i]);
        // If the length is 0, move to the next character in input
        if (!len)
        {
            i++;
            continue;
        }
        // Allocate memory for the current token in the parsed array
        parsed[k] = malloc((len + 1) * sizeof(char));
        j = 0; // Initialize index for copying characters within a token
        while (input[i] && j < len)
        {
            // Copy the character from input to the current token in the parsed array
            parsed[k][j++] = input[i++];
        }
        // Null-terminate the token in the parsed array
        parsed[k++][j] = '\0';
    }
    // Null-terminate the parsed array
    parsed[k] = NULL;
    return (parsed); // Return the array of parsed tokens
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
	EXAMPLE:
	Function call:
	t_statement *result = parser("ls -l | grep 'file.txt'");
	Return Value (Linked List of Statements):
	Resulting Linked List of Statements:
1. Command: "ls"
   - Arguments: ["-l"]
   - Operator: PIPE_OP

2. Command: "grep"
   - Arguments: ["'file.txt'"]
   - Operator: NONE
*/
/*
// PARSER 27 lines
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
		temp->next = p_new_node(get_argc(&parsed[idx[0]]));
		temp = temp->next;
	}
	temp->next = NULL;
	free(parsed);
	return (head);
}
*/


// PARSER WITH PRINTF
t_statement	*parser(char *input)
{
	char		**parsed;
	t_statement	*temp;
	t_statement	*head;
	size_t		i;
	size_t		j;
	size_t		node;

	parsed = parse_input(input);
	free(input);
	temp = p_new_node(get_argc(&parsed[0]));
	head = temp;
	i = 0;
	node = 0;
//printf("	argc head: %d\n", head->argc);
	while (parsed[i])
	{
//printf("parsed[%ld]: %s\n",i, parsed[i]);
printf("node[%ld]:\n", node);
		j = 0;
		while (parsed[i] && !is_instr(OPERATORS, parsed[i][0]))
		{
printf("		parsed[%ld]: %s\n",i, parsed[i]);
			temp->argv[j] = str_without_quotes(parsed[i]);
printf("	argv[%ld] est [%s]\n", j, temp->argv[j]);
			j++;
			i++;
		}
printf("		parsed[%ld]: %s\n",i, parsed[i]);
		temp->argv[j] = NULL;
printf("	argc current: %d\n", temp->argc);
		if (!parsed[i])
			break ;
		temp->operator = get_operator(parsed[i++]);
printf("	operator [%d]\n", temp->operator);
		temp->next = p_new_node(get_argc(&parsed[i]));
if (temp->next != NULL)
{
printf("	next yes\n");
}
		temp = temp->next;
		node++;
	}
	temp->next = NULL;
	free(parsed);
	return (head);
}
