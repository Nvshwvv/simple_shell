#include "Shell.h"
/**
 * _strlen - function that return the length of string
 * @n: the string will be chacked
 * Return: int number
*/
int _strlen(char *n)
{
	int l = 0;

	if (!n)
		return (0);
	while (*n++)
		l++;
	return (l);
}

/**
 * _strcmp - function copare two strings
 * @n: first string
 * @a: second string
 * Return: negative or positive or zero
*/
int _strcmp(char *n, char *a)
{
	while (*n && *a)
	{
		if (*n != *a)
			return (*n - *a);
		n++;
		a++;
	}
	if (*n == *a)
		return (0);
	else
		return (*n < *a ? -1 : 1);
}

/**
 * starts_with - function that check if string start with another string
 * @needle: substring to find
 * @haystack: string to search
 * Return: NULL or address of next char of haystack
*/
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - function that concates two strings
 * @destination: the destination buffer
 * @source: the source buffer
 * Return: pointer to destination buffer
*/
char *_strcat(char *destination, char *source)
{
	char *ret = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (ret);
}
