#include "shell.h"

/**
* bfree - Liberates a pointer and NULLs the address
* @ptr: address of the pointer to free
*
* Return: 1 if liberated, otherwise 0.
*/
int bfree(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}
