#include "shell.h"
/**
 * list_to_string - function that return array of strings
 * @head: ptr to first node
 * Return: an arrays of string
*/
char **list_to_string(list_t *head)
{
	size_t i = list_len(head), p;
	list_t *node = head;
	char *str;
	char **strs;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (p = 0; p < i; p++)
				free(strs[p]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}
/**
 * print_list - prints all elements of linked lists
 * @n: pointer
 * Return: size of the list
*/
size_t print_list(const list_t *n)
{
	size_t l = 0;

	while (n)
	{
		_puts(convert_number(n->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(n->str ? n->str : "(nil)");
		_puts("\n");
		n = n->next;
		l++;
	}
	return (l);
}
/**
 * node_starts_with - func return the start
 * @node: pointer to the head
 * @prefix: string to match
 * @n: the next charachter
 * Return:match node or NULL
*/
list_t *node_starts_with(list_t *node, char *prefix, char n)
{
	char *l = NULL;

	while (node)
	{
		l = starts_with(node->str, prefix);
		if (l && ((n == -1) || (*l == n)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 * get_node_index - function that gets the index of nod
 * @head: pointer to the head
 * @node: pointer to the node
 * Return: index or -1 depened on the situation
*/
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t l = 0;

	while (head)
	{
		if (head == node)
			return (l);
		head = head->next;
		l++;
	}
	return (-1);
}

/**
 * list_len - function check the lengh
 * @l: pointer to the first node
 * Return: size of len
*/
size_t list_len(const list_t *l)
{
	size_t i = 0;

	while (l)
	{
		l = l->next;
		i++;
	}
	return (i);
}
