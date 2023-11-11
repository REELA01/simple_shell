#include "shell.h"
/**
 * interactive - checl the mode
 * @i: address
 * Return: 1 on succsess
*/
int interactive(inf_o *i)
{
	return (isatty(STDIN_FILENO) && i->readfd <= 2);
}
/**
 * is_delim - see if delim
 * @c: chech char
 * @del: delim str
 * Return: 1 on success
*/
int is_delim(char c, char *del)
{
	while (*del)

		if (*del++ == c)
			return (1);
	return (0);
}
/**
 *_isalpha - see if alapha
 *@s: input char
 *Return: int value
*/
int _isalpha(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return (1);

	else
		return (0);
}
/**
 *_atoi - str to int
 *@str: string
 *Return: int value
*/
int _atoi(char *str)
{
	int sign = 1, flag = 0;
	int i, outp;
	unsigned int r = 0;

	for (i = 0;  str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;
		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			r *= 10;
			r += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		outp = -r;
	else
		outp = r;
	return (outp);
}
