#include "shell.h"
/**
 * is_chain - function test the current char in buffer is chain delimeter
 * @import: parameter struct
 * @buf: char  buffer
 * @pos:current position
 * Return: 1 if chain delim 0 other wise
*/
int is_chain(import_t *import, char *buf, size_t *pos)
{
	size_t j = *pos;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] == 0;
		j++;
		import->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		import->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		import->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*pos = j;
	return (1);
}
/**
 * check_chain - function that checks the chain
 * @import: struct params
 * @buf: char buffer
 * @pos: position
 * @i: starting in buf
 * @ln: length of buf
 * Return: NOTHING
*/
void check_chain(import_t *import, char *buf, size_t *pos, size_t i, size_t ln)
{
	size_t j = *pos;

	if (import->cmd_buf_type == CMD_AND)
	{
		if (import->status)
		{
			buf[i] = 0;
			j = ln;
		}
	}
	if (import->cmd_buf_type == CMD_OR)
	{
		if (!import->status)
		{
			buf[i] = 0;
			j = ln;
		}
	}
	*pos = j;
}
/**
 * replace_alias - replace an alias on the tokinized string
 * @import: parameter struct
 * Return: 1 or 0
*/
int replace_alias(import_t *import)
{
	int i;
	char *n;
	list_t *node;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(import->alias, import->argv[0], '=');
		if (!node)
			return (0);
		free(import->argv[0]);
		n = _strchr(node->str, '=');
		if (!n)
			return (0);
		n = _strdup(n + 1);
		if (!n)
			return (0);
		import->argv[0] = n;
	}
	return (1);
}

/**
 * replace_vars - function relace vars in tokinize string
 * @import: parameter struct
 * Return: 1 or zero
*/
int replace_vars(import_t *import)
{
	int i = 0;
	list_t *node;

	for (i = 0; import->argv[i]; i++)
	{
		if (import->argv[i][0] != '$' || !import->argv[i][1])
			continue;
		if (!_strcmp(import->argv[i], "$?"))
		{
			replace_string(&(import->argv[i]),
					_strdup(convert_number(import->status, 10, 0)));
			continue;
		}
		if (!_strcmp(import->argv[i], "$$"))
		{
			replace_string(&(import->argv[i]),
						_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(import->env, &import->argv[i][1], '=');
		if (node)
		{
			replace_string(&(import->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&import->arg[i], _strdup(""));
	}
	return (0);
}


/**
 * replace_string - function replace string
 * @old:address of old str
 * @new: the new str
 * Return: 1 or 0
*/
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
