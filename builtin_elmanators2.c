#include "Shell.h"

/**
 * _myhistory - function displays history
 * @import: strucure containing argument
 * Return: always 0
*/
int _myhistory(import_t *import)
{
	print_list(import->history);
	return (0);
}

/**
 * unset_alias - function that remove alias
 * @import: parameter struct
 * @str: the string
 * Return: always 0 (success)
*/
int unset_alias(import_t *import, char *str)
{
	char *n, c;
	int ret;

	n = _strchr(str, '-');
	if (!n)
		return (1);
	c = *n;
	*n = 0;
	ret = delete_node_at_index(&(import->alias),
			get_node_index(import->alias, node_starts_with(import->alias, str, -1)));
	*n = c;
	return (ret);
}
/**
 * set_alias - function sets alias to string
 * @import: struct parameter
 * @str: string alias
 * Return: 0 on success 1 on errorr
*/
int set_alias(import_t *import, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!++p)
		return (unset_alias(import, str));

	unset_alias(import, str);
	return (add_node_end(&(import->alias), str, 0) == NULL);
}

/**
 * print_alias - function that print an alias string
 * @node: the alais node
 * Return: always 0
*/
int print_alias(list_t *node)
{
	char *n = NULL, *s = NULL;

	if (node)
	{
		n = _strchr(node->'=');
		for (s = node->str; s <= n; s++)
			_putchar(*s);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _myalias - function that mimics the alais bulitin
 * @import: strucure containing potentioal argument
 * Return: 0 (SUCCESS)
*/
int _myalias(import_t *import)
{
	int i = 0;
	char *n = NULL;
	list_t *node = NULL;

	if (import->argc == 1)
	{
		node = import->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; import->argv[i]; i++)
	{
		n = _strchr(import->argv[i], '=');
		if (p)
			set_alias(import, import->argv[i]);
		else
			print_alias(node_starts_with(import->alias, import->argv[i], '='));
	}
	return (0);
}
