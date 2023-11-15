#include "shell.h"

/**
 * get_history_file - gets the history file
 * @import: struct parameter
 * Return: str contain history file
*/
char *get_history_file(import_t *import)
{
	char *buf, *dir;

	dir = _getenv(import, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}
/**
 * write_history - function creat a file or append an existed one
 * @import: paramter struct
 * Return: 1 or 0
*/
int write_history(import_t *import)
{
	ssize_t fd;
	char *filename = get_history_file(import);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = import->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - read the history
 * @import: struct parameter
 * Return: 1 on success 0 other wise
*/
int read_history(import_t *import)
{
	int l, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct  stat st;
	char *buf = NULL, *filename = get_history_file(import);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (l = 0; l < fsize; l++)
		if (buf[l] == '\n')
		{
			buf[l] = 0;
			build_history_list(import, buf + last, linecount++);
			last = l + 1;
		}
	if (last != l)
		build_history_list(import, buf + last, linecount++);
	free(buf);
	import->histcount = linecount;
	while (import->histcount-- >= HIST_MAX)
		delete_node_at_index(&(import->history), 0);
	renumber_history(import);
	return (import->histcount);
}
/**
 * build_history_list - add end to history liked lists
 * @import: parameter
 * @buf: a buffer
 * @linecount: histlinecount
 * Return: 0 (success)
*/

int build_history_list(import_t *import, char *buf, int linecount)
{
	list_t *node = NULL;

	if (import->history)
		node = import->history;
	add_node_end(&node, buf, linecount);

	if (!import->history)
		import->history = node;
	return (0);
}
/**
 * renumber_history - renmber the list after changed
 * @import: paramter
 * Return: new histcount
*/
int renumber_history(import_t *import)
{
	list_t *node = import->history;
	int i = 0;

	do {
		node->num = i++;
		node = node->next;
	} while (node);

	return (import->histcount = i);
}
