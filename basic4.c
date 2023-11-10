#include "shell.h"
/**
 * **strsplit - split the words with delim
 * @sn: string of input
 * @dt: the string of delim
 * Return: char value
*/
char **strsplit(char *sn, char *dt)
{
	int i, j, k, m;
	int wnum = 0;
	char **strr;

	if (sn == NULL || sn[0] == 0)
		return (NULL);
	if (!dt)
		dt = " ";
	for (i = 0; sn[i] != '\0'; i++)
		if (!is_delim(sn[i], dt) && (is_delim(sn[i + 1], dt) || !sn[i + 1]))
			wnum++;
	if (wnum == 0)
		return (NULL);
	strr = malloc((1 + wnum) * sizeof(char *));
	if (strr == NULL)
		return (NULL);
	for (i = 0, j = 0; j < wnum; j++)
	{
		while (is_delim(sn[i], dt))
			i++;
		k = 0;
		while (!is_delim(sn[i + k], dt) && sn[i + k])
			k++;
		strr[j] = malloc((k + 1) * sizeof(char));
		if (!strr[j])
		{
			for (k = 0; k < j; k++)
				free(strr[k]);
			free(strr);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			strr[j][m] = sn[i++];
		strr[j][m] = 0;
	}
	strr[j] = NULL;
	return (strr);
}
/**
 * **strsplit2 - same as strsplit but without delim cond
 * @sn: string of input
 * @delim: the delim of sepreation
 * Return: char value
*/
char **strsplit2(char *sn, char delim)
{
	int i, j, k, m;
	int wnum = 0;
	char **strr;


	if (sn == NULL || sn[0] == 0)
		return (NULL);
	for (i = 0; sn[i] != '\0'; i++)
		if ((sn[i] != delim && sn[i + 1] == delim) ||
		    (sn[i] != delim && !sn[i + 1]) || sn[i + 1] == delim)
			wnum++;
	if (wnum == 0)
		return (NULL);
	strr = malloc((1 + wnum) * sizeof(char *));
	if (strr == NULL)
		return (NULL);
	for (i = 0, j = 0; j < wnum; j++)
	{
		while (sn[i] == delim && sn[i] != delim)
			i++;
		k = 0;
		while (sn[i + k] != delim && sn[i + k] && sn[i + k] != delim)
			k++;
		strr[j] = malloc((k + 1) * sizeof(char));
		if (!strr[j])
		{
			for (k = 0; k < j; k++)
				free(strr[k]);
			free(strr);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			strr[j][m] = sn[i++];
		strr[j][m] = 0;
	}
	strr[j] = NULL;
	return (strr);
}
