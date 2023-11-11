#include "shell.h"
/**
 * _eputchar - write char
 * @c: char
 * Return: same putchar but with 2 return
*/
int _eputchar(char c)
{
	static int i;
	static char buff[W_BUF_SIZE];

	if (c == BUF_FL || i >= W_BUF_SIZE)
	{
		write(2, buff, i);
		i = 0;
	}
	if (c != BUF_FL)
		buff[i++] = c;

	return (1);
}
/**
 *_eputs - puts with error return
 * @s: string
 * Return: void value
*/
void _eputs(char *s)
{
	int j = 0;

	if (!s)
		return;

	while (s[j] != '\0')
	{
		_eputchar(s[j]);
		j++;
	}
}
/**
 * _putfd - putchar with chosen std
 * @s: printed char
 * @fd: The filedescriptor
 * Return: int value
*/
int _putfd(char s, int fd)
{
	static int i;
	static char buff[W_BUF_SIZE];

	if (s == BUF_FL || i >= W_BUF_SIZE)
	{
		write(fd, buff, i);
		i = 0;
	}
	if (s != BUF_FL)
		buff[i++] = s;
	return (1);
}
/**
 *_putsfd - same puts func with chosen std
 * @s: string
 * @fd: the filedescriptor
 * Return: int vlaue
*/
int _putsfd(char *s, int fd)
{
	int j = 0;

	if (!s)
		return (0);
	while (*s)
	{
		j += _putfd(*s++, fd);
	}
	return (j);
}
