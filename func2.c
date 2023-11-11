#include "shell.h"
/**
 * convert_number - itoa reverse
 * @num: number desired
 * @b: base of num
 * @f: flags
 * Return: char value
*/
char *convert_number(long int num, int b, int f)
{
	static char *array, buf[50];
	char *ptr, sign = 0;
	unsigned long n = num;

	if (!(f & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buf[49];
	*ptr = '\0';
	do	{
		*--ptr = array[n % b];
		n /= b;
	} while (n != 0);
	if (sign)
		*--ptr = sign;
	return (ptr);
}
/**
 * remove_comments - ignore comments
 * @buff: buffer
 * Return: void value
*/
void remove_comments(char *buff)
{
	int j;

	for (j = 0; buff[j] != '\0'; j++)
		if (buff[j] == '#' && (!j || buff[j - 1] == ' '))
		{
			buff[j] = '\0';
			break;
		}
}
/**
 * _erratoi - atoi2
 * @str: string
 * Return: int value
*/
int _erratoi(char *str)
{
	int i = 0;
	unsigned long int r = 0;

	if (*str == '+')
		str++;
	for (i = 0;  str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			r *= 10;
			r += (str[i] - '0');
			if (r > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return (r);
}
/**
 * print_d - print in desimal
 * @in: input
 * @fd: filedescriper
 * Return: printed char num
*/
int print_d(int in, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, c = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (in < 0)
	{
		_abs_ = -in;
		__putchar('-');
		c++;
	}
	else
		_abs_ = in;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			c++;
		}
		current %= i;
	}
	__putchar('0' + current);
	c++;
	return (c);
}
/**
 * print_error - error masage
 * @inf: information
 * @e: erorr string
 * Return: void value
*/
void print_error(inf_o *inf, char *e)
{
	_eputs(inf->fname);
	_eputs(": ");
	print_d(inf->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(inf->argv[0]);
	_eputs(": ");
	_eputs(e);
}
