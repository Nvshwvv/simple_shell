#include "Shell.h"
/**
 * clear_import - intialize import struct
 * @import: struct adress
 * Return: nothing
*/
void clear_import(import_t *import)
{
	import->arg = NULL;
	import->argv = NULL;
	import->argc = NULL;
	import->argc = 0;
}

/**
 * set_import - functoin insialize struct
 * @import: struct adress
 * @av: arg vec
 * Return: nothing
*/
void set_import(import_t *import, char av)
{
	int l = 0;

	import->fname = av[0];
	if (import->arg)
	{
		import->arg = strtow(info->arg, " \t");
		if (!import->argv)
		{
			import->argv = malloc(sizeof(char *) * 2);
			if (import->argv)
			{
				import->argv[0] = _strdup(import->arg);
				import->argv[1] = NULL;
			}
		}
		for (l = 0; import->argv && import->argv[l]; l++)
			;

		import->argc = l;

		replace_alias(import);
		replace_vars(import);
	}
}
/**
 * free_import - free struct
 * @import: address of struct
 * @all: true if freeing all fields
*/
void free_import(import_t *import, int all)
{
	ffree(import->argv);
	import->argv = NULL;
	import->path = NULL;
	if (all)
	{
		if (!import->cmd_buf)
			free(import->arg);
		if (import->env)
			free_list(&(import->env));
		if (import->history)
			free_list(&(import->history));
		if (import->alias)
			free_list(&(import->alias));
		ffree(import->environ);
		import->environ = NULL;
		bfree((void **) import->cmd_buf);
		if (import->readfd > 2)
			close(import->readfd);
		_putchar(BUF_FLUSH);
	}
}
