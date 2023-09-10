#include "simple.h"

/**
 * freemem - frees a pointer and NULLs the address
 * @buff: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int freemem(void **buff)
{
	if (buff && *buff)
	{
		free(*buff);
		*buff = NULL;
		return (1);
	}
	return (0);
}
