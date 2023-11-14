#include "Shell.h"
/
 * _eputs - functon print an input string
 * @str: the string will be printed
 * Return: nothing
*/
void _eputs(char *str)
{
    int l = 0;

    if (!str)
        return;
    while (str[l] != '\0')
    {
        _eputchar(str[l]);
        l++;
    }
}

/
 * _eputchar - function print input string
 * @n: te character will be printed
 * Return: -1 or 0 depend on situation
*/
int _eputchar(char n)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (n == BUF_FLUSH  i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (n != BUF_FLUSH)
        buf[i++] = n;
        return (1);
}
/**
 * _putfd - function that writes char to given fd
 * @ch: the character
 * @fd: the file descriptor
 * Return: 1 on success -1 n err
*/
int _putfd(char ch, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (ch == BUF_FLUSH  i >= WRITE_BUF_SIZE)
        {
            write(fd, buf, i);
            i = 0;
        }
        if (ch != BUF_FLUSH)
            buf[i++] = ch;
            return (1);
}
/**
 * _putsfd - function that print an input string
 * @strs: string will be printed
 * @fd: file descriptor
 * Return: num of chars
*/
int _putsfd(char *strs, int fd)
{
    int o = 0;

    if (!=strs)
        return (0);
    while (*strs)
{
    o += _putfd(*strs++, fd);
}
    return (o)
}
