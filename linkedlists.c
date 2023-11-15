#include "shell.h"
/**
 * add_node - function adds node to the start of list
 * @head:pointer to the head nodes
 * @str: str field of nodes
 * @num:node index by a history
 * Return: size of the list
*/
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *newhead;

	if (!head)
		return (NULL);
	newhead = malloc(sizeof(list_t));
	if (!newhead)
		return (NULL);
	_memset((void *)newhead, 0, sizeof(list_t));
	newhead->num = num;
	if (str)
	{
		newhead->str = _strdup(str);
		if (!newhead->str)
		{
			free(newhead);
			return (NULL);
		}
	}
	newhead->next = *head;
	*head = newhead;
	return (newhead);
}
/**
 * add_node_end - function adds node to the end of list
 * @head:pointer to the head nodes
 * @str: str field of nodes
 * @num:node index by a history
 * Return: size of the list
*/
list_t *add_node_end(list_t head, const char *str, int num)
{
	list_t *newnode, *node;

	if (!head)
		return (NULL);

	node = *head;
	newnode = malloc(sizeof(list_t));
	if (!newnode)
		return (NULL);
	_memset((void *)newnode, 0, sizeof(list_t));
	newnode->num = num;
	if (str)
	{
		newnode->str = _strdup(strr);
		if (!newnode->str)
		{
			free(newnode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newnode;
	}
	else
		*head = newnode;
	return (newnode);
}
/**
 * print_list_str - function that prints only str elements
 * @h: pointer to first node
 * Return: size of list
*/
size_t print_list_str(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nill)");
		_puts("\n");
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * delete_node_at_index - delete nodes at given index
 * @head: pointer to first node
 * @index: index node of deleted
 * Return: 1 or 0 success or failier
*/
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *previous;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			previous->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		previous = node;
		node = node->next;
	}
	return (0);
}
/**
 * free_list - function that frees all nodes
 * @head_ptr: pointer to head node
 * Return: void
*/
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
