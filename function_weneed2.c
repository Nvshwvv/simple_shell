#include "shell.h"
/**
 * _errtoi - convert str to int
 * @a: the string
 * Return: 0 or -1 its depend on situation
*/
int _errtoi(char *a)
{
	int i = 0;
	unsigned long int result = 0;

	if (*a == '+')
		a++;
	for (i = 0; a[i] != '\0'; i++)
	{
		if (a[i] >= '0' && a[i] <= '9')
	{
		result *= 10;
		result += (a[i] - '0');
		if (result > INT_MAX)
			return (-1);
	}
		else
			return (-1);
	}
	return (result);
}
/**
 * print_error - func that print err messege
 * @import: parameter
 * @erstr: string containing specified err messege
 * Retuen: 0 or 1 or -1 depend on the situation
*/
void print_error(import_t *import, char *erstr)
{
	_eputs(import->fname);
	_eputs(": ");
	print_d(import->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(import->argv[0]);
	_eputs(": ");
	_eputs(erstr);
}
/**
 * print_d - function print decimal numbers
 * @ip: the input
 * @fd: filedescriptor
 * Return: num of characters
*/
int print_d(int ip, int fd)
{
	int (*___putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		___putchar = _eputchar;
	if (ip < 0)
	{
		_abs_ = -ip;
		___putchar('-');
		count++;
	}
	else
		_abs_ = ip;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			___putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	___putchar('0' + current);
	count++;

	return (count);
}
/**
 * convert_number - function that convert
 * @n: number
 * @basic: the base
 * @flags: the flag
 * Return: string
*/
char *convert_number(long int n, int basic, int flags)
{
	static char *array;
	static char buffer[50];
	char *ptr;
	char sign = 0;
	unsigned long a = n;

	if (!(flags & CONVERT_UNSIGNED) && n < 0)
	{
		a = -n;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';
	do {
		*--ptr = array[a % basic];
		a /= basic;
	} while (a != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comment - function that remmove comments
 * @buf: address to modified string
 * Return: 0
*/
void remove_comment(char *buf)
{
	int l;

	for (l = 0; buf[l] != '\0' l++)
		if (buf[l] == '#' && (!l || buf[l - 1] == ' '))
		{
			buf[l] = '\0';
			break;
		}
}
