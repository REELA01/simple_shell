#include "shell.h"
/**
 * add_node - adds node at first
 * @h: head
 * @s: string in node
 * @num: node
 * Return: list size
*/
lis_t *add_node(lis_t **h, const char *s, int num)
{
	lis_t *new_head;

	if (h == NULL)
		return (NULL);
	new_head = malloc(sizeof(lis_t));
	if (new_head == NULL)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(lis_t));
	new_head->num = num;
	if (s)
	{
		new_head->str = _strdup(s);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *h;
	*h = new_head;

	return (new_head);
}
/**
 * add_node_end - adds a node last
 * @h: head node
 * @s: string of node
 * @num: node num
 * Return: list size
*/
lis_t *add_node_end(lis_t **h, const char *s, int num)
{
	lis_t *new_node, *node;

	if (h == NULL)
		return (NULL);

	node = *h;
	new_node = malloc(sizeof(lis_t));
	if (new_node == NULL)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(lis_t));
	new_node->num = num;
	if (s)
	{
		new_node->str = _strdup(s);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*h = new_node;
	return (new_node);
}
/**
 * print_list_str - prints node string
 * @head: headeer
 * Return: list size
*/
size_t print_list_str(const lis_t *head)
{
	size_t j = 0;

	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		j++;
	}
	return (j);
}
/**
 * delete_node_at_index - deletes node according to index
 * @h: headder
 * @index: delete location
 * Return: int vaule
*/
int delete_node_at_index(lis_t **h, unsigned int index)
{
	lis_t *node, *pre;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);
	if (!index)
	{
		node = *h;
		*h = (*h)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (i == index)
		{
			pre->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		pre = node;
		node = node->next;
	}
	return (0);
}
/**
 * free_list - free nodes
 * @h_ptr: to head ptr
 * Return: void value
*/
void free_list(lis_t **h_ptr)
{
	lis_t *node, *next_n, *h;

	if (!h_ptr || !*h_ptr)
		return;
	h = *h_ptr;
	node = h;
	while (node)
	{
		next_n = node->next;
		free(node->str);
		free(node);
		node = next_n;
	}
	*h_ptr = NULL;
}
