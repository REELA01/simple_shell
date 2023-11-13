#include "shell.h"
/**
 * is_chain - check chain delimeter
 * @inf: inforamtion struct
 * @buff: char
 * @ptr: address of buff postion
 * Return: int value 0 or 1
*/
int is_chain(inf_o *inf, char *buff, size_t *ptr)
{
	size_t j = *ptr;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buff[j] == ';')
	{
		buff[j] = 0;
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = j;
	return (1);
}
/**
 * check_chain - checks chainng status like or and and
 * @inf: information struct
 * @buff: char
 * @ptr: current postion address of buff
 * @i: starting point of buff
 * @l: len of buff
 * Return: void value
*/
void check_chain(inf_o *inf, char *buff, size_t *ptr, size_t i, size_t l)
{
	size_t j = *ptr;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buff[i] = 0;
			j = l;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buff[i] = 0;
			j = l;
		}
	}
	*ptr = j;
}
/**
 * replace_string - replace old str with new one
 * @o: old str address
 * @n: new str
 * Return: int value 0 or 1
*/
int replace_string(char **o, char *n)
{
	free(*o);
	*o = n;
	return (1);
}
/**
 * replace_alias - replace otginal with desired alias
 * @inf: information strcut
 * Return: int value 0 or 1
*/
int replace_alias(inf_o *inf)
{
	int j;
	lis_t *node;
	char *ptr;

	for (j = 0; j < 10; j++)
	{
		node = node_starts_with(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		inf->argv[0] = ptr;
	}
	return (1);
}
/**
 * replace_vars - get the value of variable in env
 * @inf: information struct
 * Return: int value 0 or 1
*/
int replace_vars(inf_o *inf)
{
	int j = 0;
	lis_t *node;

	for (j = 0; inf->argv[j]; j++)
	{
		if (inf->argv[j][0] != '$' || !inf->argv[j][1])
			continue;
		if (!_strcmp(inf->argv[j], "$?"))
		{
			replace_string(&(inf->argv[j]),
				_strdup(convert_number(inf->status, 10, 0)));
			continue;
		}
		if (!_strcmp(inf->argv[j], "$$"))
		{
			replace_string(&(inf->argv[j]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(inf->env, &inf->argv[j][1], '=');
		if (node)
		{
			replace_string(&(inf->argv[j]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&inf->argv[j], _strdup(""));
	}
	return (0);
}
