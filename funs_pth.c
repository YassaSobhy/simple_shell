#include "simple.h"

/**
 * execmd - determines if a file is an executable command
 * @kno: the info struct
 * @ln: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int execmd(info_t *kno, char *ln)
{
	struct stat pn;

	(void)kno;
	if (!ln || stat(ln, &pn))
		return (0);

	if (pn.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * chdupl - duplicates characters
 * @strp: the PATH string
 * @bgnn: starting index
 * @frbdn: stopping index
 *
 * Return: pointer to new buffer
 */
char *chdupl(char *strp, int bgnn, int frbdn)
{
	static char str[1024];
	int x = 0, r = 0;

	for (r = 0, x = bgnn; x < frbdn; x++)
		if (strp[x] != ':')
			str[r++] = strp[x];
	str[r] = 0;
	return (str);
}

/**
 * pthserch - finds this cmd in the PATH string
 * @ins: the info struct
 * @pbuff: the PATH string
 * @inpt: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *pthserch(info_t *ins, char *pbuff, char *inpt)
{
	int i = 0, wrkpos = 0;
	char *path;

	if (!pbuff)
		return (NULL);
	if ((_strlen(inpt) > 2) && starts_with(inpt, "./"))
	{
		if (execmd(ins, inpt))
			return (inpt);
	}
	while (1)
	{
		if (!pbuff[i] || pbuff[i] == ':')
		{
			path = chdupl(pbuff, wrkpos, i);
			if (!*path)
				_strcat(path, inpt);
			else
			{
				_strcat(path, "/");
				_strcat(path, inpt);
			}
			if (execmd(ins, path))
				return (path);
			if (!pbuff[i])
				break;
			wrkpos = i;
		}
		i++;
	}
	return (NULL);
}
