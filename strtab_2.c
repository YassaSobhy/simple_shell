#include "simple.h"

/**
 * lenlst - determines length of linked list
 * @k: pointer to first node
 *
 * Return: size of list
 */
size_t lenlst(const list_t *k)
{
	size_t j = 0;

	while (k)
	{
		k = k->next;
		j++;
	}
	return (j);
}

/**
 * lsttstr - returns an array of strings of the list->str
 * @frst: pointer to first node
 *
 * Return: array of strings
 */
char **lsttstr(list_t *frst)
{
	list_t *node = frst;
	size_t i = lenlst(frst), j;
	char **strs;
	char *str;

	if (!frst || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * lstdis - prints all elements of a list_t linked list
 * @ptr: pointer to first node
 *
 * Return: size of list
 */
size_t lstdis(const list_t *ptr)
{
	size_t y = 0;

	while (ptr)
	{
		_puts(numconv(ptr->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(ptr->str ? ptr->str : "(nil)");
		_puts("\n");
		ptr = ptr->next;
		y++;
	}
	return (y);
}

/**
 * stndwth - returns node whose string starts with prefix
 * @nd: pointer to list head
 * @strt: string to match
 * @h: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *stndwth(list_t *nd, char *strt, char h)
{
	char *f = NULL;

	while (nd)
	{
		f = starts_with(nd->str, strt);
		if (f && ((h == -1) || (*f == h)))
			return (nd);
		nd = nd->next;
	}
	return (NULL);
}

/**
 * recndix - gets the index of a node
 * @hd: pointer to list head
 * @nd: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t recndix(list_t *hd, list_t *nd)
{
	size_t a = 0;

	while (hd)
	{
		if (hd == nd)
			return (a);
		hd = hd->next;
		a++;
	}
	return (-1);
}
