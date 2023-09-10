#include "simple.h"

/**
 **_fillmemory - fills memory with a constant byte
 *@str: the pointer to the memory area
 *@k: the byte to fill *s with
 *@m: the amount of bytes to be filled
 *Return: (str) a pointer to the memory area s
 */
char *_fillmemory(char *str, char k, unsigned int m)
{
	unsigned int var;

	for (var = 0; var < m; var++)
		str[var] = k;
	return (str);
}

/**
 * rreset - frees a string of strings
 * @t: string of strings
 */
void rreset(char **t)
{
	char **sr = t;

	if (!t)
		return;
	while (*t)
		free(*t++);
	free(sr);
}

/**
 * _redef - reallocates a block of memory
 * @let: pointer to previous malloc'ated block
 * @presize: byte size of previous block
 * @modisize: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_redef(void *let, unsigned int presize, unsigned int modisize)
{
	char *s;

	if (!let)
		return (malloc(modisize));
	if (!modisize)
		return (free(let), NULL);
	if (modisize == presize)
		return (let);

	s = malloc(modisize);
	if (!s)
		return (NULL);

	presize = presize < modisize ? presize : modisize;
	while (presize--)
		s[presize] = ((char *)let)[presize];
	free(let);
	return (s);
}
