#include "minishell.h"

/**
 * @brief Calculates the number of digits in a given long long integer.
 *
 * This function calculates and returns the number of digits in a long long 
 * integer 'n'.
 *
 * @param n The long long integer to calculate the number of digits for.
 * @return The number of digits in 'n'.
 */
static long long	ft_digits(long long n)
{
	long long	digits;

	digits = 0;
	if (n <= 0)
		digits += 1;
	while (n != 0)
	{
		n /= 10;
		digits += 1;
	}
	return (digits);
}

/**
 * @brief Converts a long long integer to a string.
 *
 * This function converts a long long integer 'n' to a string and returns 
 * the result.
 *
 * @param n The long long integer to convert to a string.
 * @return A dynamically allocated string containing the converted value of 'n'.
 *         The caller is responsible for freeing the allocated memory.
 */

char	*ft_llinttoarray(long long n)
{
	long long	digits;
	int			signal;
	char		*result;

	digits = ft_digits(n);
	signal = 1;
	result = malloc((digits + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[digits--] = '\0';
	if (n < 0)
	{
		signal = -1;
		result[0] = '-';
	}
	else if (n == 0)
		result[0] = '0';
	while (n != 0)
	{
		result[digits--] = (n % 10 * signal) + '0';
		n /= 10;
	}
	return (result);
}