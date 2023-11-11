#include "shell.h"
/**
 * clear_info - clear information
 * @inf: address
*/
void clear_info(inf_o *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}
/**
 * set_info - set the struct
 * @inf: address
 * @av: vector
*/
void set_info(inf_o *inf, char **av)
{
	int i = 0;

	inf->fname = av[0];
	if (inf->arg)
	{
		inf->argv = strsplit(info->arg, " \t");
		if (!inf->argv)
		{
			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (i = 0; inf->argv && inf->argv[i]; i++)
			;
		inf->argc = i;
		replace_alias(inf);
		replace_vars(inf);
	}
}
/**
 * free_info - free inf_o struct
 * @inf: address
 * @all: include all
*/
void free_info(inf_o *inf, int all)
{
	ffree(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;

	if (all)
	{
		if (!inf->cmd_buf)
			free(inf->arg);
		if (inf->env)
			free_list(&(inf->env));
		if (inf->history)
			free_list(&(inf->history));
		if (inf->alias)
			free_list(&(inf->alias));
		ffree(inf->environ);
			inf->environ = NULL;
		free_ad((void **)inf->cmd_buf);
		if (inf->readfd > 2)
			close(inf->readfd);
		_putchar(BUF_FL);
	}
}
