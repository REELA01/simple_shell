#include "shell.h"
/**
 * list_len - strlen of linked list
 * @head: first node ptr
 * Return: list size
*/
size_t list_len(const lis_t *head)
{
	size_t j = 0;

	while (head)
	{
		head = head->next;
		j++;
	}
	return (j);
}
/**
 * list_to_strings - array of node strings
 * @h: head ptr
 * Return: char value
*/
char **list_to_strings(lis_t *h)
{
	lis_t *node = h;
	size_t i = list_len(h), j;
	char **strr, *str;

	if (!h || !i)
		return (NULL);
	strr = malloc(sizeof(char *) * (i + 1));
	if (strr == NULL)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strr[j]);
			free(strr);
			return (NULL);
		}
		str = _strcpy(str, node->str);
		strr[i] = str;
	}
	strr[i] = NULL;
	return (strr);
}
/**
 * print_list - print linked list in string2
 * @head: head node ptr
 * Return: list size
*/
size_t print_list(const lis_t *head)
{
	size_t j = 0;

	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		j++;
	}
	return (j);
}
/**
 * node_starts_with - find node start with desired text
 * @h: ptr to list head
 * @text: string to match
 * @c: the next char
 * Return: desired node
*/
lis_t *node_starts_with(lis_t *h, char *text, char c)
{
	char *ptr = NULL;

	while (h)
	{
		ptr = starts_with(h->str, text);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (h);
		h = h->next;
	}
	return (NULL);
}
/**
 * get_node_index - node at index
 * @h: head ptr
 * @ind: ptr of node
 * Return: node or -1
*/
ssize_t get_node_index(lis_t *h, lis_t *ind)
{
	size_t j = 0;

	while (h)
	{
		if (h == ind)
			return (j);
		h = h->next;
		j++;
	}
	return (-1);
}
