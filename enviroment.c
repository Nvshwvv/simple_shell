#include "Shell.h"


/**
 * _getenv - function that gets the value of an environ
 * @import: structure contaaining args
 * @name: env variable name
 * Return: value
*/
char *_getenv(import_t *import, const char name)
{
	list_t *node = import->env;
	char *n;

	while (node)
	{
		n = starts_with(node->str, name);
		if (n && *n)
			return (n);
		node = node->next;
	}
	return (NULL);
}
/**
 * _myenv - function that print current enviroment
 * @import: structure
 * Return: 0 (SUCCESS)
*/
int _myenv(import_t *import)
{
	print_list_str(import->env);
	return (0);
}
/**
 * _mysetenv - function that initial new enviroment
 * @import: strucure
 * Return: 0 (success)
*/
int _mysetenv(import_t *import)
{
	if (import->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(import, import->argv[1], import->argv[2]))
		return (0);
	return (1);
}
/**
 * _myunsetenv - function unset enviroments
 * @import: address of strucuture
 * Return: always 0
*/
int _myunsetenv(import_t *import)
{
	int n;

	if (import->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (n = 1; n <= import->argc; n++)
	_unsetenv(import, import->argv[n]);

	return (0);
}
/**
 * populate_env_list - function that remove enviromet value
 * @import: structure
 * Return: always 0
*/
int populate_env_list(import_t *import)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	import->env = node;
	return (0);
}
