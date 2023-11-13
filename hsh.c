#include "shell.h"
/**
 * find_builtin_c - find the command to func
 * @inf: information struct
 * Return: int value
*/
int find_builtin_c(inf_o *inf)
{
	int i, builtin_r = -1;

	builtin_tab tab[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"unsetenv", _myunsetenv},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; tab[i].type; i++)
		if (_strcmp(inf->argv[0], tab[i].type) == 0)
		{
			inf->line_count++;
			builtin_r = tab[i].func(inf);
			break;
		}
	return (builtin_r);
}
/**
 * fork_cmd - deo fork func in cmd
 * @inf: information strcut
 * Return: void value
*/
void fork_cmd(inf_o *inf)
{
	pid_t ch_pid;

	ch_pid = fork();
	if (ch_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (ch_pid == 0)
	{
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_info(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_error(inf, "Permission denied\n");
		}
	}
}
/**
 * find_cmd - srearcu comm in path
 * @inf: information struct
 * Return: void value
*/
void find_cmd(inf_o *inf)
{
	char *path = NULL;
	int i, j;

	inf->path = inf->argv[0];
	if (inf->linecount_flag == 1)
	{
		inf->line_count++;
		inf->linecount_flag = 0;
	}
	for (i = 0, j = 0; inf->arg[i]; i++)
		if (!is_delim(inf->arg[i], " \t\n"))
			j++;
	if (!j)
		return;
	path = find_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		fork_cmd(inf);
	}
	else
	{
		if ((interactive(inf) || _getenv(inf, "PATH=")
			|| inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
			fork_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_error(inf, "not found\n");
		}
	}
}
/**
 * hsh - main loop
 * @inf: information struct
 * @av: arg vector
 * Return: int value 0 or 1
*/
int hsh(inf_o *inf, char **av)
{
	ssize_t k = 0;
	int builtin_r = 0;

	while (k != -1 && builtin_r != -2)
	{
		clear_info(inf);
		if (interactive(inf))
			_puts("$ ");
		_eputchar(BUF_FL);
		k = get_input(inf);
		if (k != -1)
		{
			set_info(inf, av);
			builtin_r = find_builtin_c(inf);
			if (builtin_r == -1)
				find_cmd(inf);
		}
		else if (interactive(inf))
			_putchar('\n');
		free_info(inf, 0);
	}
	write_history(inf);
	free_info(inf, 1);
	if (!interactive(inf) && inf->status)
		exit(inf->status);
	if (builtin_r == -2)
	{
		if (inf->err_num == -1)
			exit(inf->status);
		exit(inf->err_num);
	}
	return (builtin_r);
}
