#include "shell.h"
/**
 * populate_env_list - inisiate enivroment node
 * @inf: information struct
 * Return: int vlaue 0
*/
int populate_env_list(inf_o *inf)
{
	lis_t *n = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&n, environ[j], 0);
	inf->env = n;

	return (0);
}
/**
 * _myenv - prints enviroment
 * @inf: to enviroment info
 * Return: int value 0
*/
int _myenv(inf_o *inf)
{
	print_list_str(inf->env);
	return (0);
}
/**
 * _getenv - search var
 * @inf: where to search
 * @n: env varriable name
 * Return: char vlaue
*/
char *_getenv(inf_o *inf, const char *n)
{
	lis_t *node = inf->env;
	char *pp;

	while (node)
	{
		pp = starts_with(node->str, n);
		if (pp && *pp)
			return (pp);
		node = node->next;
	}
	return (NULL);
}
/**
 * _mysetenv - add new var or modify it
 * @inf: information struct
 *  Return: int vlaue 0
*/
int _mysetenv(inf_o *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);

	return (1);
}
/**
 * _myunsetenv - delete var
 * @inf: information struct
 *  Return: int value 0
*/
int _myunsetenv(inf_o *inf)
{
	int j;

	if (inf->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= inf->argc; j++)
		_unsetenv(inf, inf->argv[j]);
	return (0);
}
