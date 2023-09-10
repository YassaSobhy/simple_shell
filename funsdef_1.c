#include "simple.h"

/**
 * mode_detect - returns true if shell is interactive mode
 * @dta: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int mode_detect(info_t *dta)
{
	return (isatty(STDIN_FILENO) && dta->readfd <= 2);
}

/**
 * checkspace - checks if character is a delimeter
 * @ch: the char to check
 * @spc: the delimeter string
 * Return: 1 if true, 0 if false
 */
int checkspace(char ch, char *spc)
{
	while (*spc)
		if (*spc++ == ch)
			return (1);
	return (0);
}

/**
 *_checkalpha - checks for alphabetic character
 *@let: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _checkalpha(int let)
{
	if ((let >= 'a' && let <= 'z') || (let >= 'A' && let <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_contint - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _contint(char *str)
{
	int k, sn = 1, flg = 0, opt;
	unsigned int res = 0;

	for (k = 0;  str[k] != '\0' && flg != 2; k++)
	{
		if (str[k] == '-')
			sn *= -1;

		if (str[k] >= '0' && str[k] <= '9')
		{
			flg = 1;
			res *= 10;
			res += (str[k] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (sn == -1)
		opt = -res;
	else
		opt = res;

	return (opt);
}
