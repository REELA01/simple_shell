#include "shell.h"
/**
 * _strlen - find the length
 * @str: string
 * Return: j value
 */
int _strlen(char *str)
{
	int j = 0;


	if (str == NULL)
		return (0);
	while (*str++)
		j++;
	return (j);
}
/**
 * _strcmp - compare between 2 strings
 * @str1:string1
 * @str2: string2
 * Return: int value
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2
				)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)

		return (0);

		return (*str1 < *str2 ? -1 : 1);
}
/**
 * starts_with - see the start
 * @hk: what we search
 * @n: all string
 * Return: the adress of desired string
 */
char *starts_with(const char *hk, const char *n)
{
	while (*n)
		if (*n++ != *hk++)
			return (NULL);

	return ((char *)hk);
}
/**
 * _strcat - conecting strings
 * @d: place
 * @s: source
 * Return: dest pointer
 */
char *_strcat(char *d, char *s)
{
	char *i = d;


	while (*d)
		d++;
	while (*s)
		*d++ = *s++;
	*d = *s;
	return (i);
}
