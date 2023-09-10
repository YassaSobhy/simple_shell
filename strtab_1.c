#include "simple.h"

/**
 * defnode - adds a node to the start of the list
 * @mng: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *defnode(list_t **mng, const char *str, int num)
{
	list_t *new_head;

	if (!mng)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_fillmemory((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *mng;
	*mng = new_head;
	return (new_head);
}

/**
 * nodetend - adds a node to the end of the list
 * @pr: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *nodetend(list_t **pr, const char *str, int num)
{
	list_t *new_node, *node;

	if (!pr)
		return (NULL);

	node = *pr;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_fillmemory((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*pr = new_node;
	return (new_node);
}

/**
 * listdistr - prints only the str element of a list_t linked list
 * @sn: pointer to first node
 *
 * Return: size of list
 */
size_t listdistr(const list_t *sn)
{
	size_t z = 0;

	while (sn)
	{
		_puts(sn->str ? sn->str : "(nil)");
		_puts("\n");
		sn = sn->next;
		z++;
	}
	return (z);
}

/**
 * de_spec_node - deletes node at given index
 * @frst: address of pointer to first node
 * @x: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int de_spec_node(list_t **frst, unsigned int x)
{
	list_t *nd, *prend;
	unsigned int i = 0;

	if (!frst || !*frst)
		return (0);

	if (!x)
	{
		nd = *frst;
		*frst = (*frst)->next;
		free(nd->str);
		free(nd);
		return (1);
	}
	nd = *frst;
	while (nd)
	{
		if (i == x)
		{
			prend->next = nd->next;
			free(nd->str);
			free(nd);
			return (1);
		}
		i++;
		prend = nd;
		nd = nd->next;
	}
	return (0);
}

/**
 * redflst - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void redflst(list_t **head_ptr)
{
	list_t *node, *senode, *hd;

	if (!head_ptr || !*head_ptr)
		return;
	hd = *head_ptr;
	node = hd;
	while (node)
	{
		senode = node->next;
		free(node->str);
		free(node);
		node = senode;
	}
	*head_ptr = NULL;
}
