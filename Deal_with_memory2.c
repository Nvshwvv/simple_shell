#include "Shell.h"
/**
* bfree - function that frees a pointer 
* @ptrs: address of the pointer will be freed
* Return: 1 if freed, 0 if otherwise
*/
int bfree(void **ptrs)
{
    if (ptrs && *ptrs)
    {
        free(*ptrs);
        *ptrs = NULL;
        return (1);
    }
    return (0);
}
