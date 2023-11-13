#include "shell.h"
/**
 * sigintHandl - hanle sig
 * @sig_num: the signal num
 * Return: void value
*/
void sigintHandl(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FL);
}
/**
 * input_buff - buff chained command
 * @inf: information struct
 * @buff: buffer adress
 * @l: length
 * Return: size of byte
*/
ssize_t input_buff(inf_o *inf, char **buff, size_t *l)
{
	ssize_t r = 0;
	size_t l_p = 0;

	if (!*l)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandl);
#if USE_GETLINE
		r = getline(buff, &l_p, stdin);
#else
		r = _getline(inf, buff, &l_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0';
				r--;
			}
			inf->linecount_flag = 1;
			remove_comments(*buff);
			build_hist_list(inf, *buff, inf->histcount++);
			{
				*l = r;
				inf->cmd_buf = buff;
			}
		}
	}
	return (r);
}
/**
 * read_buff - read from inf struct
 * @inf: information struct
 * @buff: the buffer holding str
 * @i: hold size
 * Return: the size of R
*/
ssize_t read_buff(inf_o *inf, char *buff, size_t *i)
{
	ssize_t R = 0;

	if (*i)
		return (0);
	R = read(inf->readfd, buff, R_BUF_SIZE);
	if (R >= 0)
		*i = R;
	return (R);
}
/**
 * get_input - get a line of chain
 * @inf: information struct
 * Return: size of bytes
*/
ssize_t get_input(inf_o *inf)
{
	static char *buff;
	static size_t i, j, l;
	ssize_t r = 0;
	char **buf_p = &(inf->arg), *pp;

	_putchar(BUF_FL);
	r = input_buff(inf, &buff, &l);
	if (r == -1)
		return (-1);
	if (l)
	{
		j = i;
		pp = buff + i;
		check_chain(inf, buff, &j, i, l);
		while (j < l)
		{
			if (is_chain(inf, buff, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= l)
		{
			i = l = 0;
			inf->cmd_buf_type = CMD_NORM;
		}
		*buf_p = pp;
		return (_strlen(pp));
	}
	*buf_p = buff;
	return (r);
}
/**
 * _getline - getline func
 * @inf: infomation struct
 * @ptr: address pointer to buff
 * @l: size of ptr
 * Return: itn vlaue str
*/
int _getline(inf_o *inf, char **ptr, size_t *l)
{
	static char buff[R_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, str = 0;
	char *pp = NULL, *new_p = NULL;
	char *c;

	pp = *ptr;
	if (pp && l)
		str = *l;
	if (i == len)
		i = len = 0;
	r = read_buff(inf, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(pp, str, str ? str + k : k + 1);
	if (!new_p)
		return (pp ? free(pp), -1 : -1);
	if (str)
		_strncat(new_p, buff + i, k - i);
	else
		_strncpy(new_p, buff + i, k - i + 1);
	str += k - i;
	i = k;
	pp = new_p;
	if (l)
		*l = str;
	*ptr = pp;
	return (str);
}
