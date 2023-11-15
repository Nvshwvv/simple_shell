#include "shell.h"

/**
 * is_cmd - function determind if the file is executable file
 * @import: structuer contains a poteantioal argument
 * @path: path to file
 * Return: 1 if true, other wise will be 0
*/
int is_cmd(import_t *import, char *path)
{
	struct stat st;

	(void)import;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - function duplicate charactars
 * @pathstr: THE PATH STRING:
 * @start: the starting index
 * @stop: stoping index
 * Return: pointer to new buffer
*/
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int p = 0, k = 0;

	for (k = 0, p = start; p < stop; p++)
		if (pathstr[p] != ':')
			buf[k++] = pathstr[p];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - function finds the cmd in the path string
 * @import: import struct
 * @pathstr: THE PATH STRING
 * @cmd: THE COMMAND
 * Return: full path or NULL
*/
char *find_path(import_t *import, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(import, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(import, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);

}
