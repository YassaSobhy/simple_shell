#include "simple.h"

/**
 * **strtow - splits a string into words.
 * @str: the input string
 * @del: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *del)
{
	int i, j, x, y, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!checkspace(str[i], del) && (checkspace(str[i + 1], del) || !str[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (checkspace(str[i], del))
			i++;
		x = 0;
		while (!checkspace(str[i + x], del) && str[i + x])
			x++;
		s[j] = malloc((x + 1) * sizeof(char));
		if (!s[j])
		{
			for (x = 0; x < j; x++)
				free(s[x]);
			free(s);
			return (NULL);
		}
		for (y = 0; y < x; y++)
			s[j][y] = str[i++];
		s[j][y] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtow2 - splits a string into words.
 * @str: the input string
 * @del: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char del)
{
	int i, j, x, y, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != del && str[i + 1] == del) ||
		    (str[i] != del && !str[i + 1]) || str[i + 1] == del)
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == del && str[i] != del)
			i++;
		x = 0;
		while (str[i + x] != del && str[i + x] && str[i + x] != del)
			x++;
		s[j] = malloc((x + 1) * sizeof(char));
		if (!s[j])
		{
			for (x = 0; x < j; x++)
				free(s[x]);
			free(s);
			return (NULL);
		}
		for (y = 0; y < x; y++)
			s[j][y] = str[i++];
		s[j][y] = 0;
	}
	s[j] = NULL;
	return (s);
}
