#include "Shell.h"
/
* *_memset - function that fills the memory with a constant bytes
* @s: pointer to memory area
* @b: num of bytes 
* @n: amount of bytes filled
*/
char *_memset(char *s, char b, unsigned int n)
{
    unsigned int w;

    for (w = 0; w < n; w++)
        s[i] = b;
    return (s);
}
/
* ffree - function that frees string of string
* @ss: string of string
*/
void ffree(char ss)
{
    char **e = ss;

    if (!ss)
        return;
    while (*ss)
        free (*ss++);
    free (e);
}

/
* _realloc - reallocat blocks in a memory 
* @ptr: pointer 
* @nwsize: bytees size of new block
* @oldsize: bytes size of the old block
* Return: pointer
*/
void *_realloc(void *ptr, unsigned int oldsize, unsigned int nwsize)
{
    char *n;

    if (!ptr)
        return (malloc(nwsize));
    if (!nwsize)
        return (free(ptr), NULL);
    if (nwsize == oldsize)
        return (ptr);

    n = malloc(nwsize);
    if (!n)
        return (NULL);

    oldsize = oldsize < nwsize ? oldsize : nwsize;
    while (oldsize--)
        n[oldsize] = ((char *)ptr) [oldsize];
    free(ptr);
    return (n);
}
