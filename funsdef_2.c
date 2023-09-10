#include "simple.h"

/**
 * _strtint - converts a string to an integer
 * @pr: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _strtint(char *pr)
{
	int k = 0;
	unsigned long int final = 0;

	if (*pr == '+')
		pr++;  /* TODO: why does this make main return 255? */
	for (k = 0;  pr[k] != '\0'; k++)
	{
		if (pr[k] >= '0' && pr[k] <= '9')
		{
			final *= 10;
			final += (pr[k] - '0');
			if (final > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (final);
}

/**
 * errordis - prints an error message
 * @instr: the parameter & return info struct
 * @ptr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void errordis(info_t *instr, char *ptr)
{
	_eputs(instr->fname);
	_eputs(": ");
	deciprint(instr->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(instr->argv[0]);
	_eputs(": ");
	_eputs(ptr);
}

/**
 * deciprint - function prints a decimal (integer) number (base 10)
 * @ips: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int deciprint(int ips, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, n = 0;
	unsigned int _abs_, runnow;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (ips < 0)
	{
		_abs_ = -ips;
		__putchar('-');
		n++;
	}
	else
		_abs_ = ips;
	runnow = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + runnow / j);
			n++;
		}
		runnow %= j;
	}
	__putchar('0' + runnow);
	n++;

	return (n);
}

/**
 * numconv - converter function, a clone of itoa
 * @nums: number
 * @b: base
 * @flg: argument flags
 *
 * Return: string
 */
char *numconv(long int nums, int b, int flg)
{
	static char *a;
	static char buf[50];
	char sn = 0;
	char *sttr;
	unsigned long m = nums;

	if (!(flg & CONVERT_UNSIGNED) && nums < 0)
	{
		m = -nums;
		sn = '-';

	}
	a = flg & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	sttr = &buf[49];
	*sttr = '\0';

	do	{
		*--sttr = a[m % b];
		m /= b;
	} while (m != 0);

	if (sn)
		*--sttr = sn;
	return (sttr);
}

/**
 * remocomnt - function replaces first instance of '#' with '\0'
 * @sr: address of the string to modify
 *
 * Return: Always 0;
 */
void remocomnt(char *sr)
{
	int n;

	for (n = 0; sr[n] != '\0'; n++)
		if (sr[n] == '#' && (!n || sr[n - 1] == ' '))
		{
			sr[n] = '\0';
			break;
		}
}
