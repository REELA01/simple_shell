#include "shell.h"
/**
 * main - Entry point
 * @ac: arguemnt count
 * @av: argument vector
 * Return: 1 sucssec or 0 otherwise
*/
int main(int ac, char **av)
{
	inf_o inf[] = { INFO_INIT };
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
				_eputchar(BUF_FL);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readfd = fd;
	}
	populate_env_list(inf);
	read_history(inf);
	hsh(inf, av);
	return (EXIT_SUCCESS);
}
