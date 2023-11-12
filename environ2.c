#include "shell.h"
/**
 * _unsetenv - delete var from env
 * @inf: information strcut
 * @va: varuable
 * Return: int vlaue 0
*/
int _unsetenv(inf_o *inf, char *va)
{
	lis_t *node = inf->env;
	size_t i = 0;
	char *ptr;

	if (!node || !va)
		return (0);

	while (node)
	{
		ptr = starts_with(node->str, va);
		if (ptr && *ptr == '=')
		{
			inf->env_changed = delete_node_at_index(&(inf->env), i);
			i = 0;
			node = inf->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (inf->env_changed);
}
/**
 * _setenv - to put a new env var
 * @inf: information struct
 * @va: variable
 * @val: its value
 *  Return: int value 0
*/
int _setenv(inf_o *inf, char *va, char *val)
{
	char *buff = NULL, *pp;
	lis_t *node;

	if (!va || !val)
		return (0);
	buff = malloc(_strlen(va) + _strlen(val) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, va);
	_strcat(buff, "=");
	_strcat(buff, val);
	node = inf->env;
	while (node)
	{
		pp = starts_with(node->str, va);
		if (pp && *pp == '=')
		{
			free(node->str);
			node->str = buff;
			inf->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(inf->env), buff, 0);
	free(buff);
	inf->env_changed = 1;
	return (0);
}
/**
 * get_environ - get the string array copy of env
 * @inf: information struct
 * Return: char value
*/
char **get_environ(inf_o *inf)
{
	if (!inf->environ || inf->env_changed)
	{
		inf->environ = list_to_strings(inf->env);
		inf->env_changed = 0;
	}
	return (inf->environ);
}
