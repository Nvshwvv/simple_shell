#include "shell.h"
/**
 * _puts - function print input string
 * @str: the string that will be printed
 * Return: nothing
*/
void _puts(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		_putchar(str[n]);
		n++;
	}
}
/**
 * _putchar - functions print character to stdout
 * @n: the character
 * Return: -1 on success 1 on error
*/
int _putchar(char n)
{
	static int l;
	static char buf[WRITE_BUF_SIZE];

	if (n == BUF_FLUSH || l > WRITE_BUF_SIZE)
	{
		write(1, buf, l);
		l = 0;
	}
	if (n != BUF_FLUSH)
	buf[l++] = n;
	return (1);
}

/**
 * _strcpy - function that copy a string
 * @desti: the destination
 * @srcs: the source
 * Return: pointer to destination
*/
char *_strcpy(char *desti, char *srcs)
{
	int l = 0;

	if (desti == srcs || srcs == 0)
		return (desti);
	while (srcs[l])
	{
		desti[l] = srcs[l];
		l++;
	}
	desti[l] = 0;
	return (desti);
}

/**
 * _strdup - function that duplicate string
 * @str: the sting will be duplicated
 * Return: pointer
*/
char *_strdup(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (ret);
}
