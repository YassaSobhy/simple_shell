#include "simple.h"

/**
 * _exit_function - exits the shell
 * @info: Structure containing potential arguments.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _exit_function(info_t *info)
{
	int exit_test;

	if (info->argv[1])
	{
		exit_test = _strtint(info->argv[1]);
		if (exit_test == -1)
		{
			info->status = 2;
			errordis(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _strtint(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _cd_function - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _cd_function(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _get_env(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_get_env(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		errordis(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _get_env(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help_function - changes the current directory of the process
 * @info: Structure containing potential arguments.
 *  Return: Always 0
 */
int _help_function(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
