#include "shell.h"

/**
 * main - entry point
 * @ac: argument counter
 * @av: argument vector
 * Return: 0 or 1 success or failier
*/
int main(int ac, int **av)
{
	import_t import[] = { IMPORT_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
	"add $3, %0"
	: "=r" (fd)
	: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILUER);
		}
		import->readfd = fd;
	}
	populate_env_list(import);
	read_history(import);
	hsh(import, av);
	return (EXIT_SUCCESS);
}
