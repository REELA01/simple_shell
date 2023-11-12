#include "shell.h"
/**
 * _myhelp - do help to call
 * @inf: info struct
 *  Return: int value 0
*/
int _myhelp(inf_o *inf)
{
	char **arg_ar;


	arg_ar = inf->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_ar);
	return (0);
}
/**
 * _myexit - do exit function
 * @inf: information strcut
 *  Return: int value
*/
int _myexit(inf_o *inf)
{
	int ch;

	if (inf->argv[1])
	{
		ch = _erratoi(inf->argv[1]);
		if (ch == -1)
		{
			inf->status = 2;
			print_error(inf, "Illegal number: ");
			_eputs(inf->argv[1]);
			_eputchar('\n');
			return (1);
		}
		inf->err_num = _erratoi(inf->argv[1]);
		return (-2);
	}
	inf->err_num = -1;
	return (-2);
}
/**
 * _mycd - work with the currne dir
 * @inf: info struct
 *  Return: int value 0
*/
int _mycd(inf_o *inf)
{
	char *str, *dir, buff[1024];
	int chdir_ret;

	str = getcwd(buff, 1024);
	if (!str)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dir = _getenv(inf, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(inf, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(inf->argv[1], "-") == 0)
	{
		if (!_getenv(inf, "OLDPWD="))
		{
			_puts(str);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(inf, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = _getenv(inf, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(inf->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(inf, "can't cd to ");
		_eputs(inf->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(inf, "OLDPWD", _getenv(inf, "PWD="));
		_setenv(inf, "PWD", getcwd(buff, 1024));
	}
	return (0);
}
