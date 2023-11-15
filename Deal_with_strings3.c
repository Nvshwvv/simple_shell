#include "shell.h"
/**
 * *_strncpy - function that copies a string
 * @desti: the destination
 * @srcs: the source
 * @n: the number of characters that to be copied
 * Return: sting
*/
char *_strncpy(char *desti, char *srcs, int n)
{
	int i, j;
	char *s = desti;

	i = 0;
	while (srcs[i] != '\0' && i < n - 1)
	{
		desti[i] = srcs[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			desti[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * *_strncat - concates two strings
 * @desti: the first string
 * @srcs: the second string
 * @n: num of bytes
 * Return: the concates string
*/
char *_strncat(char *desti, char *srcs, int n)
{
	int i, j;
	char *s = desti;

	i = 0;
	j = 0;
	while (desti[i] != '\0')
		i++;
	while (srcs[j] != '\0' && j < n)
	{
		desti[i] = srcs[j];
		i++;
		j++;
	}
	if (j < n)
		desti[i] = '\0';
	return (s);
}

/**
 * *_strchr - function locates a character in string
 * @s: the string parsed
 * @c: the character to look for
 * Return: (s) pointer  to memory
*/
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
