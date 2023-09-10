#include "simple.h"

/**
 * main_shll - main shell loop
 * @inst: the parameter & return info struct
 * @avar: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int main_shll(info_t *inst, char **avar)
{
	ssize_t t = 0;
	int ret = 0;

	while (t != -1 && ret != -2)
	{
		clear_info(inst);
		if (mode_detect(inst))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		t = get_input(inst);
		if (t != -1)
		{
			set_info(inst, avar);
			ret = srch_bltin(inst);
			if (ret == -1)
				fcmd(inst);
		}
		else if (mode_detect(inst))
			_putchar('\n');
		free_info(inst, 0);
	}
	write_history(inst);
	free_info(inst, 1);
	if (!mode_detect(inst) && inst->status)
		exit(inst->status);
	if (ret == -2)
	{
		if (inst->err_num == -1)
			exit(inst->status);
		exit(inst->err_num);
	}
	return (ret);
}

/**
 * srch_bltin - finds a builtin command
 * @guid: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int srch_bltin(info_t *guid)
{
	int k, tr = -1;
	builtin_table builtintbl[] = {
		{"exit", _exit_function},
		{"env", _myenv},
		{"help", _help_function},
		{"history", _history_func},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _cd_function},
		{"alias", _alias_func},
		{NULL, NULL}
	};

	for (k = 0; builtintbl[k].type; k++)
		if (_strcmp(guid->argv[0], builtintbl[k].type) == 0)
		{
			guid->line_count++;
			tr = builtintbl[k].func(guid);
			break;
		}
	return (tr);
}

/**
 * fcmd - finds a command in PATH
 * @st: the parameter & return info struct
 *
 * Return: void
 */
void fcmd(info_t *info)
{
	char *path = NULL;
	int n, m;

	info->path = info->argv[0];
	if (info->lineCount_flag == 1)
	{
		info->line_count++;
		info->lineCount_flag = 0;
	}
	for (n = 0, m = 0; info->arg[n]; n++)
		if (!checkspace(info->arg[n], " \t\n"))
			m++;
	if (!m)
		return;

	path = pthserch(info, _get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		cmdfrk(info);
	}
	else
	{
		if ((mode_detect(info) || _get_env(info, "PATH=")
			|| info->argv[0][0] == '/') && execmd(info, info->argv[0]))
			cmdfrk(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			errordis(info, "not found\n");
		}
	}
}

/**
 * cmdfrk - forks a an exec thread to run cmd
 * @in: the parameter & return info struct
 *
 * Return: void
 */
void cmdfrk(info_t *in)
{
	pid_t chgtpid;

	chgtpid = fork();
	if (chgtpid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (chgtpid == 0)
	{
		if (execve(in->path, in->argv, get_environ(in)) == -1)
		{
			free_info(in, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(in->status));
		if (WIFEXITED(in->status))
		{
			in->status = WEXITSTATUS(in->status);
			if (in->status == 126)
				errordis(in, "Permission denied\n");
		}
	}
}
