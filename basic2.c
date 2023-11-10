#include "shell.h"
/**
 * _strcpy - take the copy of string to anotherr
 * @d: place
 * @s: sorce of string
 * Return: cahr value
 */
char *_strcpy(char *d, char *s)
{
	int j = 0;

	if (d == s || s == 0)
		return (d);

	while (s[j])
	{
		d[j] = s[j];
		j++;
	}
	d[j] = 0;
	return (d);
}
/**
 * _strdup - make a dup of string
 * @strr: string
 * Return: char value
 */
char *_strdup(const char *strr)
{
	int l = 0;
	char *buf;

	if (strr == NULL)
		return (NULL);
	while (*strr++)
		l++;
	buf = malloc(sizeof(char) * (l + 1));

	if (!buf)
		return (NULL);
	for (l++; l--;)
		buf[l] = *--strr;
	return (buf);
}
/**
 *_puts - puts function
 *@strr: string
 * Return: void value
 */
void _puts(char *strr)
{
	int j = 0;

	if (!strr)
		return;

	while (strr[j] != '\0')
	{
		_putchar(strr[j]);
		j++;
	}
}
/**
 * _putchar - putchar func
 * @c: The char
 * Return: succsses1
 */
int _putchar(char c)
{
	static int j;
	static char buffer[W_BUF_SIZE];


	if (c == BUF_FL || j >= W_BUF_SIZE)
	{
		write(1, buffer, j);
		j = 0;
	}
	if (c != BUF_FL)
		buffer[j++] = c;
	return (1);
}
