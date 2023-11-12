#include "shell.h"
/**
 * build_hist_list - intiate hist lenked list
 * @inf: information struct
 * @buff: buffer
 * @lcount: the hist linecount
 * Return: int value 0
*/
int build_hist_list(inf_o *inf, char *buff, int lcount)
{
	lis_t *node = NULL;

	if (inf->history)
		node = inf->history;
	add_node_end(&node, buff, lcount);
	if (!inf->history)
		inf->history = node;
	return (0);
}
/**
 * renumber_hist - renumbers the hist when more then max
 * @inf: information struct
 * Return: new count
*/
int renumber_hist(inf_o *inf)
{
	lis_t *node = inf->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (inf->histcount = j);
}
/**
 * get_hist_file - get histfile
 * @inf: information struct
 * Return: char value
*/
char *get_hist_file(inf_o *inf)
{
	char *buff, *dir;

	dir = _getenv(inf, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}
/**
 * write_history - write hist
 * @inf: information stuct
 * Return: int value
*/
int write_history(inf_o *inf)
{
	ssize_t fd;
	lis_t *node = NULL;
	char *fn = get_hist_file(inf);

	if (!fn)
		return (-1);
	fd = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (fd == -1)
		return (-1);
	for (node = inf->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FL, fd);
	close(fd);
	return (1);
}
/**
 * read_history - read hist
 * @inf: information struct
 * Return: int value
*/
int read_history(inf_o *inf)
{
	int i, last = 0, lcount = 0;
	char *buff = NULL, *fn = get_hist_file(inf);
	ssize_t fd, rdlen, flsize = 0;
	struct stat st;

	if (!fn)
		return (0);
	fd = open(fn, O_RDONLY);
	free(fn);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		flsize = st.st_size;
	if (flsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (flsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, flsize);
	buff[flsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < flsize; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_hist_list(inf, buff + last, lcount++);
			last = i + 1;
		}
	if (last != i)
		build_hist_list(inf, buff + last, lcount++);
	free(buff);
	inf->histcount = lcount;
	while (inf->histcount-- >= HIST_MAX)
		delete_node_at_index(&(inf->history), 0);
	renumber_hist(inf);
	return (inf->histcount);
}
