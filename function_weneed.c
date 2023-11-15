#include "shell.h"
/**
 * interactive - function that return 1 if shell in interactive mode
 * @import: struct adress
 * Return: 1 if in interactive 0 if otherwis
*/
int interactive(import_t *import)
{
	return (isatty(STDIN_FILENO) && import->readfd <= 2);
}

/**
 * is_delim - function that checks if character is delimeter
 * @delim: delimter string
 * @ch: the char to check
 * Return: 1 if true 0 otherwise
*/
int is_delim(char ch, char *delim)
{
	while (*delim)
		if (*delim++ == ch)
			return (1);
	return (0);
}
/**
 * _isalpha - function that checks for alphabetic
 * @ch: the char
 * Return: 1 if alphabetic 0 if other
*/
int _isalpha(int *ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - convert a string to an integer
 * @a: the string
 * Return: 0 or 1
*/

int _atoi(char *a)
{
	int i, sign = 1, flag = 0, op;
	unsigned int res = 0;

	for (i = 0; a[i] != '\0' && flag != 2; i++)
	{
		if (a[i] == '-')
			sign *= -1;

	if (a[i] >= '0' && a[i] <= '9')
	{
		flag = 1;
		res *= 10;
		res += (a[i] - '0');
	}
	else if (flag == 1)
		flag = 2;
	}
	if (sign == -1)
		op = -res;
	else
		op = res;

	return (op);
}
