#include "simple.h"

/**
 * testch - test if current char in buffer is a chain delimeter
 * @pt: the parameter struct
 * @str: the char buffer
 * @s: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int testch(info_t *pt, char *str, size_t *s)
{
	size_t x = *s;

	if (str[x] == '|' && str[x + 1] == '|')
	{
		str[x] = 0;
		x++;
		pt->cmd_buf_type = CMD_OR;
	}
	else if (str[x] == '&' && str[x + 1] == '&')
	{
		str[x] = 0;
		x++;
		pt->cmd_buf_type = CMD_AND;
	}
	else if (str[x] == ';') /* found end of this command */
	{
		str[x] = 0; /* replace semicolon with null */
		pt->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*s = x;
	return (1);
}

/**
 * shchain - checks we should continue chaining based on last status
 * @inps: the parameter struct
 * @ptr: the char buffer
 * @h: address of current position in buf
 * @q: starting position in buf
 * @counts: length of buf
 *
 * Return: Void
 */
void shchain(info_t *inps, char *ptr, size_t *h, size_t q, size_t counts)
{
	size_t f = *h;

	if (inps->cmd_buf_type == CMD_AND)
	{
		if (inps->status)
		{
			ptr[q] = 0;
			f = counts;
		}
	}
	if (inps->cmd_buf_type == CMD_OR)
	{
		if (!inps->status)
		{
			ptr[q] = 0;
			f = counts;
		}
	}

	*h = f;
}

/**
 * chalias - replaces an aliases in the tokenized string
 * @ch: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int chalias(info_t *ch)
{
	int l;
	list_t *node;
	char *gr;

	for (l = 0; l < 10; l++)
	{
		node = stndwth(ch->alias, ch->argv[0], '=');
		if (!node)
			return (0);
		free(ch->argv[0]);
		gr = _strchr(node->str, '=');
		if (!gr)
			return (0);
		gr = _strdup(gr + 1);
		if (!gr)
			return (0);
		ch->argv[0] = gr;
	}
	return (1);
}

/**
 * vars_ch - replaces vars in the tokenized string
 * @st: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int vars_ch(info_t *st)
{
	int k = 0;
	list_t *node;

	for (k = 0; st->argv[k]; k++)
	{
		if (st->argv[k][0] != '$' || !st->argv[k][1])
			continue;

		if (!_strcmp(st->argv[k], "$?"))
		{
			restring(&(st->argv[k]),
				_strdup(numconv(st->status, 10, 0)));
			continue;
		}
		if (!_strcmp(st->argv[k], "$$"))
		{
			restring(&(st->argv[k]),
				_strdup(numconv(getpid(), 10, 0)));
			continue;
		}
		node = stndwth(st->env, &st->argv[k][1], '=');
		if (node)
		{
			restring(&(st->argv[k]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		restring(&st->argv[k], _strdup(""));

	}
	return (0);
}

/**
 * restring - replaces string
 * @pre: address of old string
 * @modi: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int restring(char **pre, char *modi)
{
	free(*pre);
	*pre = modi;
	return (1);
}
