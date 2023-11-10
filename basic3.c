#include "shell.h"
/**
 * *_strncpy - same of strcpy but int
 * @d: where to copy
 * @s: string
 * @num: the size
 * Return: char value
*/
char *_strncpy(char *d, char *s, int num)
{
	int i = 0, j;
	char *str = d;

	while (s[i] != '\0' && i < num - 1)
	{
		d[i] = s[i];
		i++;
	}

	if (i < num)
	{
		j = i;
		while (j < num)
		{
			d[j] = '\0';
			j++;
		}
	}

	return (str);
}
/**
 * *_strncat - same of strcat but with num
 * @d: where is 1 string to
 * @s: string
 * @num: size
 * Return: cahr value
*/
char *_strncat(char *d, char *s, int num)
{
	int i = 0, j = 0;
	char *str = d;

	while (d[i] != '\0')
		i++;
	while (s[j] != '\0' && j < num)
	{
		d[i] = s[j];
		i++;
		j++;
	}
	if (j < num)
		d[i] = '\0';

	return (str);
}
/**
 * *_strchr - find char in string
 * @str: string
 * @c: to be found
 * Return: char value
*/
char *_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');
	return (NULL);
}
