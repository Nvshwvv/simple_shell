#icnclude "Shell.h"
/**
 * get_environ - function that returns string array cpy of environ
 * @import: strucure containing arguments
 * Return: 0 (SUCCESS)
*/
char **get_environ(import_t *import)
{
	if (!import->environ || import->env_changed)
	{
		import->environ = list_to_strings(import->env);
		import->env_changed = 0;
	}
	return (import->environ);
}
/**
 * _unsetenv - function that remvove enviroment variable
 * @import: strucure contaaining args
 * @var: enviroment variable
 * Return: string env var property
*/
int _unsetenv(import_t *import, char *var)
{
	list_t *node = import->env;
	size_t i = 0;
	char *n;

	if (!node || !var)
		return (0);
	while (node)
	{
		n = starts_with(node->str, var);
		if (n && *n == '=')
		{
			import->env_changed = delete_node_at_index(&(import->env), i);
			i = 0;
			node = import->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (import->env_changed);
}
/**
 * _setenv - function that initialize a new enviroment variable
 * @import: structer contain args
 * @var: string env var property
 * @value: string env var
 * Return: 0 (ALWAYS)
*/
int _setenv(import_t *import, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = import->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			import->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(import->env), buf, 0);
	free(buf);
	import->env_changed = 1;
	return (0);
}
