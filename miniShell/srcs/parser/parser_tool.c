#include "minishell.h"

/*
	get_argc, is_spaces, streq, get_operator, p_new_node, get_nb_statements, 
	get_token_len, and parse_input. These functions are used to perform tasks 
	like counting arguments, comparing strings, and parsing the input into 
	tokens.
*/
/**
 * Get the number of non-operator arguments in an array of strings.
 * 
 * This function iterates through an array of strings and counts the number of
 * elements that are not single-character operators. It returns the count.
 *
 * @param parsed - An array of strings to analyze.
 * @return The count of non-operator arguments in the array.
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

/**
 * Check if a character is a whitespace character.
 * 
 * This function determines whether a given character is a whitespace character,
 * including space, tab, newline, vertical tab, form feed, or carriage return.
 *
 * @param c - The character to check.
 * @return True if the character is a whitespace character, otherwise false.
 */
bool	is_spaces(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (true);
	return (false);
}

/**
 * Checks if two strings are equal.
 *
 * @param {char*} str1 - The first string to compare.
 * @param {char*} str2 - The second string to compare.
 * @return {bool} True if the strings are equal, false otherwise.
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

/**
 * Get the operator type corresponding to a given operator string.
 *
 * @param {char} *operator - The operator string to be checked.
 *
 * @returns {t_operator} - The operator type determined from the string.
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