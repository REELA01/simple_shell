#include "shell.h"
/**
 * print_alias - print alias func
 * @n: node
 * Return: int value 0 or 1
*/
int print_alias(lis_t *n)
{
	char *pp = NULL;
	char *a = NULL;

	if (n)
	{
		pp = _strchr(n->str, '=');
		for (a = n->str; a <= pp; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(pp + 1);
		_puts("'\n");
		return (0);
	}

	return (1);
}
/**
 * unset_alias - unset it
 * @inf: info struct
 * @s: alias string
 * Return: int value 0 or 1
*/
int unset_alias(inf_o *inf, char *s)
{
	char *pp, c;
	int r;

	pp = _strchr(s, '=');
	if (!pp)
		return (1);
	c = *pp;
	*pp = 0;
	r = delete_node_at_index(&(inf->alias),
		get_node_index(inf->alias, node_starts_with(inf->alias, s, -1)));
	*pp = c;
	return (r);
}
/**
 * set_alias - set alias
 * @inf: info struct
 * @s: alais string
 * Return: int value 0 or 1
*/
int set_alias(inf_o *inf, char *s)
{
	char *pp;

	pp = _strchr(s, '=');
	if (!pp)
		return (1);
	if (!*++pp)
		return (unset_alias(inf, s));
	unset_alias(inf, s);
	return (add_node_end(&(inf->alias), s, 0) == NULL);
}
/**
 * _myalias - it manual
 * @inf: info struct
 *  Return: int value 0
*/
int _myalias(inf_o *inf)
{
	int i = 0;
	lis_t *node = NULL;
	char *pp = NULL;

	if (inf->argc == 1)
	{
		node = inf->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; inf->argv[i]; i++)
	{
		pp = _strchr(inf->argv[i], '=');
		if (pp)
			set_alias(inf, inf->argv[i]);
		else
			print_alias(node_starts_with(inf->alias, inf->argv[i], '='));
	}
	return (0);
}
/**
 * _myhistory - displays the hist list
 * @inf: info struct
 *  Return: int value 0
*/
int _myhistory(inf_o *inf)
{
	print_list(inf->history);
	return (0);
}
