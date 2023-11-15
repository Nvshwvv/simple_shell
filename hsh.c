#include "shell.h"

/**
 * hsh - THE MAIN GREAT SHELL WE DO
 * @import: struct parameter
 * @av: the argument vector
 * Return: 0 or 1 its depend on suuccess or fail
*/
int hsh(import_t *import, char **av)
{
	ssize_t n = 0;
	int builtin_ret = 0;

	while (n != -1 && builtin_ret != -2)
	{
		clear_import(import);
		if (interactive(import))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		n = get_input(import);
		if (n != -1)
		{
			set_import(import, av);
			builtin_ret = find_builtin(import);
			if (builtin_ret == -1)
				find_cmd(import);
		}
		else if (interactive(import))
			_putchar('\n');
		free_import(import, 0);
	}
	write_history(import);
	free_import(import, 1);
	if (!interactive(import) && import->status)
		exit(import->status);
	if (builtin_ret == -2)
	{
		if (import->err_num == -1)
			exit(import->status);
		exit(import->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - function that finds the builtin commands
 * @import: struct parameter
 * Return: -1, 1, 0, 1, -2 it's depened on thesituation
*/
int find_builtin(import_t *import)
{
	int n, built_in_ret = -1;
	builtin_table builtintbl[] = {
	{"exit", _myexit},
	{"env", _myenv},
	{"help", _myhelp},
	{"history", _myhistory},
	{"setenv", _mysetenv},
	{"unsetenve", _myunsetenv},
	{"cd", _mycd},
	{"alias", _myalias},
	{NULL, NULL}
	};
	for (n = 0; builtintbl[n].type; n++)
		if (_strcmp(import->argv[0], builtintbl[n].type) == 0)
		{
			import->line_count++;
			built_in_ret = builtintbl[n].func(import);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - function that find the command
 * @import: struct parms
 * Return: 0 or 1
*/
void find_cmd(import_t *import)
{
	char *path = NULL;
	int j, k;

	import->path = import->argv[0];
	if (import->linecount_flag == 1)
	{
		import->line_count++;
		import->linecount_flag = 0;
	}
	for (j = 0, k = 0; import->arg[j]; j++)
		if (!is_delim(import->arg[j], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(import, _getenv(import, "PATH="), import->argv[0]);
	if (path)
	{
		import->path = path;
		fork_cmd(import);
	}
	else
	{
		if ((interactive(import) || _getenv(import, "PATH=") /
					|| import->argv[0][0] == '/') && is_cmd(import, import->argv[0]))
			fork_cmd(import);
		else if (*(import->arg) != '\n')
		{
			import->status = 127;
			print_error(import, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks an executable thread to run cmd
 * @import: struct params
 * Return: nothing
*/
void fork_cmd(import_t *import)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(import->path, import->argv, get_environ(import)) == -1)
		{
			free_import(import, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(import->status));
		if (WIFEXITED(import->status))
		{
			import->status = WEXITSTATUS(import->status);
			if (import->status == 126)
				print_error(import, "Permission denied\n");
		}
	}
}
