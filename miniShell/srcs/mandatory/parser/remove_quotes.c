#include <minishell.h>


/*
    Function that will return the size of the string without the quotes
*/
size_t	size_without_quotes(char *parsed)
{
	size_t	size;
	size_t	i;
	char	quote;

	quote = '\0';
	i = 0;
	size = 0;
	while (parsed[i])
	{
		while (parsed[i] && (!is_instr(QUOTES, parsed[i])))
		{
			i++;
			size++;
		}
		if (!parsed[i])
			break;
		quote = parsed[i++];
		while (parsed[i] && (parsed[i] != quote))
		{
			i++;
			size++;
		}
		quote = '\0';
	}
	return (size);
}

/*
    Function that will return a string without the quotes
    It will be used mainly with echo
*/
char	*str_without_quotes(char *parsed)
{
	size_t	i;
	size_t	j;
	char	quote;
	char	*unquoted_parsed;

	i = 0;
	j = 0;
	quote = '\0';
	unquoted_parsed = malloc(sizeof(char) * (size_without_quotes(parsed) + 1));
	while (parsed[i])
	{
		while (parsed[i] && (!is_instr(QUOTES, parsed[i])))
			unquoted_parsed[j++] = parsed[i++];
		if (!parsed[i])
			break;
		quote = parsed[i++];
		while (parsed[i] && (parsed[i] != quote))
			unquoted_parsed[j++] = parsed[i++];
		quote = '\0';
	}
	unquoted_parsed[j] = '\0';
//	free (parsed);
	return (unquoted_parsed);
}

// things to do
/*
alloc and free parsed
*/

// MALLOC NOTES
/*
- i have malloc of unquoted_parsed
*/

/*
int main(int ac, char **av)
{
    (void)ac;
    printf("%ld\n", size_without_quotes(av[1]));
	char *str = str_without_quotes(av[1]);
	printf("%s\n", str);
	free(str);
    return 0;
}
*/
