#include "shell.h"
/**
 * is_cmd - if file is an executable
 * @inf: infoamtion struct
 * @pa: path of file
 * Return: int value 1 or 0
*/
int is_cmd(inf_o *inf, char *pa)
{
	struct stat st;

	(void)inf;
	if (!pa || stat(pa, &st))
		return (0);
	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * dup_chars - dup char
 * @pastr: path strring
 * @start: parameter
 * @stop: paramaeter
 * Return: char value
*/
char *dup_chars(char *pastr, int start, int stop)
{
	static char buff[1024];
	int i = 0;
	int j = 0;

	for (j = 0, i = start; i < stop; i++)
		if (pastr[i] != ':')
			buff[j++] = pastr[i];
	buff[j] = 0;
	return (buff);
}
/**
 * find_path - finds current mai directory
 * @inf: information struct
 * @pastr: path string
 * @cmd: tehe current main dir to find
 * Return: the desired path or null
*/
char *find_path(inf_o *inf, char *pastr, char *cmd)
{
	int j = 0;
	int cur_pos = 0;
	char *path;

	if (!pastr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pastr[j] || pastr[j] == ':')
		{
			path = dup_chars(pastr, cur_pos, j);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(inf, path))
				return (path);
			if (!pastr[j])
				break;
			cur_pos = j;
		}
		j++;
	}
	return (NULL);
}
