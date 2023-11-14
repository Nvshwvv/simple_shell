#include "Shell.h"
/**
 * **strtow - function that spiling string into words
 * @str: the input string
 * @delim: the delimeter
 * Return: a pointer to an arrays of string
*/
char **strtow(char *str, char *delim)
{
	int i, j, k, m, nw = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!delim)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
	if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim) || !str[i + 1]))
		nw++;

	if (nw == 0)
		return (NULL);
	s = malloc((1 + nw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nw; j++)
	{
		while (is_delim(str[i], delim))
			i++;
		k = 0;
		while (!is_delim(str[i + k], delim) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - function that spiling string into words
 * @str: the input string
 * @delim: the delimeter
 * Return: a pointer to an arrays of string
*/
char **strtow2(char *str, char *delim)
{
	int i, j, k, m, nw = 0;
	char **s;

	if (str == NULL  str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim)  !str[i + 1]))
			nw++;

	if (nw == 0)
		return (NULL);
	s = malloc((1 + nw) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < nw; j++)
	{
		while (is_delim(str[i], delim))
			i++;
		k = 0;
	while (!is_delim(str[i + k], delim) && str[i + k])
		k++;
	s[j] = malloc((k + 1) * sizeof(char));
	if (!s[j])
	{
		for (k = 0; k < j; k++)
			free(s[k]);
		free(s);
		return (NULL);
	}
	for (m = 0; m < k; m++)
		s[j][m] = str[i++];
	s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
