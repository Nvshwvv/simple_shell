#include "Shell.h"

/
 * input_buf - buffers chained commands
 * @import: struct parameter
 * @buf: buffer address
 * @len: len var address
 * Return: bytes read
*/
ssize_t input_buf(import_t *import, char **buf, size_t *len)
{
    ssize_t n = 0;
    size_t len_p = 0;

    if (!*len)
    {
        free(*buf);
        *buf = NULL;
        signal(SIGNT, signhandler);
#if USE_GETLINE
    n = getline(buf, &len_p, stdin);
#else
    n = _getline(import, buf, &len_p);
#endif
    if (n > 0)
    {
        if ((*buf) [n - 1] == '\n')
        {
            (*buf)[n - 1] = '\0';
            n--;
        }
        import->linecount_flag = 1;
        remove_comment(*buf);
        build_history_list(import, *buf, import->histcount++);
    {
        *len = n;
        import->cmd_buf = buf;
    }
    }
    }
    return (n);
}

/
 * get_input - function get the line
 * @import: struct params
 * Return: bytes read
*/
ssize_t get_input(import_t *import)
{
    static char *buf;
    static size_t i, j, len;
    char buf_p = &(import->arg), *p;
    ssize_t r = 0;

    _putchar(BUF_FLUSH);r = input_buf(import, &buf, &len);
    if (r == -1)
        return (-1);
    if (len)
    {
        j = i;
        p = buf + i;

        check_chain(import, buf, &j, i, len);
        while (j < len)
        {
            if (is_chain(import, buf, &j))
                break;
            j++;
        }
        i = j + 1;
        if (i >= len)
        {
            i = len = 0;
            import->cmd_buf_type = CMD_NORM;
        }
        *buf_p = p;
        return (_strlen(p));
    }
    *buf_p = buf;
    return (r);
}

/
 * read_buf - function reads a buffer
 * @import: struct params
 * @buf: buffer
 * @n: size
 * Return: the size
*/
ssize_t read_buf(import_t *import, char *buf, ssize *n)
{
    ssize_t p = 0;

    if (!n)
        return (0);
    p = read(import->readfd, buf, READ_BUF_SIZE);
    if (p >= 0)
        *n = p;
    return (p);
}

/
 * _getline - my own get line
 * @import: strct parameter
 * @ptr: address of pointer
 * @length: the length
 * Return: the size
*/
int _getline(import_t *import, char **ptr, size_t *length)
{
    static char buf[READ_BUF_SIZE];
    static size_t i, len;
    size_t k;
    char *p = NULL, *np = NULL, *C;
    ssize_t r = 0, s = 0;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    r = read_buf(import, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return (-1);

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    np = _realloc(p, s, s ? s + k : k + 1);
    if (!np)
        return (p ? free(p), -1 : -1);
    
    if (s)
        _strcat(np, buf + i, k - i);
    else
        _strncpy(np, buf + i, k - i + 1);
    
    s += k - i;
    i = k;
    p = np;

    if (length)
        *length = s;
    *ptr = p;
    return (s);
}

/
 * signhandler - handle the sign
 * @sign: the sign num
 * Return: nothing
*/
void signhandler(__attribute__9((unused))int sign)
{
    _puts("\n");
    _puts("$ ");
    _putchar(BUF_FLUSH);
}
