#include "minishell.h"

/**
 * @brief Checks if a character is a digit (0-9).
 *
 * This function checks whether a given character is a digit in the range '0' 
 * to '9'.
 *
 * @param c The character to check.
 * @return true if the character is a digit, false otherwise.
 */
bool	is_digit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (true);
	return (false);
}