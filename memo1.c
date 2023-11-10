#include "shell.h"
/**
 **_memset - puts the desired size
 *@m: pointer
 *@d: within the byte
 *@size: the size of the bytes
 *Return: char value
*/
char *_memset(char *m, char d, unsigned int size)
{
	unsigned int j;

	for (j = 0; j < size; j++)
		m[i] = d;
	return (m);
}
/**
 * ffree - free function
 * @sstr: string
*/
void ffree(char **sstr)
{
	char **i = sstr;

	if (!sstr)
		return;

	while (*sstr)
		free(*sstr++);
	free(i);
}
/**
 * _realloc - reaalloc function
 * @pointer: pointr of old size
 * @old_size: old desied size
 * @new_size: new desired size
 * Return: void value
*/
void *_realloc(void *pointer, unsigned int old_size, unsigned int new_size)
{
	char *pp;

	if (!pointer)
		return (malloc(new_size));
	if (!new_size)
		return (free(pointer), NULL);
	if (new_size == old_size)
		return (pointer);
	pp = malloc(new_size);
	if (!pp)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		pp[old_size] = ((char *)pointer)[old_size];
	free(pointer);
	return (pp);
}
