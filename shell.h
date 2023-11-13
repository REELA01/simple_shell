#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define BUF_FL -1
#define R_BUF_SIZE 1024
#define W_BUF_SIZE 1024
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096
#define USE_GETLINE 0
#define USE_STRTOK 0

extern char **environ;
/**
 * struct list_str - linkedl
 * @num: number of integer
 * @str: the string int he node
 * @next: to next node
*/
typedef struct list_str
{
	int num;
	char *str;

	struct list_str *next;
} lis_t;
/**
 *struct pass_info - passs desired function
 *@arg: argument string
 *@argv: arg array
 *@path: the path of the argument
 *@argc: arg size
 *@line_count: error related
 *@err_num: exit after error
 *@linecount_flag: flag count
 *@fname: name of file
 *@env: envioron copy
 *@environ: copy of environ from LL env
 *@history: hisnode
 *@alias: alaiasnode
 *@env_changed: env vairation
 *@status: status of the last execd command
 *@cmd_buf: address to cmd_buf
 *@cmd_buf_type: logic
 *@readfd: read fd
 *@histcount: lines of history
*/
typedef struct pass_info
{
	int err_num;
	int linecount_flag;
	int env_changed;
	int status;
	int cmd_buf_type;
	char *arg;
	char **argv;
	char *path;
	char *fname;
	char **environ;
	char **cmd_buf;
	int argc;
	int readfd;
	int histcount;
	unsigned int line_count;
	lis_t *env;
	lis_t *history;
	lis_t *alias;
} inf_o;

#define INFO_INIT \
{0, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0, \
	NULL, NULL, NULL}
/**
 *struct builtin - contain a builtin string
 *@type: comm flag
 *@func: fuction
*/
typedef struct builtin
{
	char *type;
	int (*func)(inf_o *);
} builtin_tab;

/*hsh*/
int find_builtin_c(inf_o *inf);
void fork_cmd(inf_o *inf);
void find_cmd(inf_o *inf);
int hsh(inf_o *inf, char **av);
/* path_1 */
int is_cmd(inf_o *inf, char *pa);
char *dup_chars(char *pastr, int start, int stop);
char *find_path(inf_o *inf, char *pastr, char *cmd);
/* loophsh.c */
int loophsh(char **);
/*basic1*/
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
/*basic2*/
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
/*basic3*/
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
/*basic4*/
char **strsplit(char *, char *);
char **strsplit2(char *, char);
/* memo1*/
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
/* memo2 */
int free_ad(void **);
/*func1*/
int interactive(inf_o *i);
int is_delim(char c, char *del);
int _isalpha(int s);
int _atoi(char *str);
/*func2*/
char *convert_number(long int num, int b, int f);
void remove_comments(char *buff);
int _erratoi(char *str);
int print_d(int in, int fd);
void print_error(inf_o *inf, char *e);
/* llist1*/
lis_t *add_node(lis_t **h, const char *s, int num);
lis_t *add_node_end(lis_t **h, const char *s, int num);
size_t print_list_str(const lis_t *head);
int delete_node_at_index(lis_t **h, unsigned int index);
void free_list(lis_t **h_ptr);
/*llist2*/
size_t list_len(const lis_t *head);
char **list_to_strings(lis_t *h);
size_t print_list(const lis_t *head);
lis_t *node_starts_with(lis_t *h, char *text, char c);
ssize_t get_node_index(lis_t *h, lis_t *ind);
/*err.fi*/
int _eputchar(char c);
void _eputs(char *s);
int _putfd(char s, int fd);
int _putsfd(char *s, int fd);
/*minf*/
void clear_info(inf_o *inf);
void set_info(inf_o *inf, char **av);
void free_info(inf_o *inf, int all);
/*enviorn1*/
int populate_env_list(inf_o *inf);
int _myenv(inf_o *inf);
char *_getenv(inf_o *inf, const char *n);
int _mysetenv(inf_o *inf);
int _myunsetenv(inf_o *inf);
/*like1*/
int _myhelp(inf_o *inf);
int _myexit(inf_o *inf);
int _mycd(inf_o *inf);
/*alias*/
int _myalias(inf_o *);
int _myhistory(inf_o *);
/*alot2*/
ssize_t get_input(inf_o *inf);
int _getline(inf_o *inf, char **ptr, size_t *l);
void sigintHandl(int);
/*environ2*/
int _unsetenv(inf_o *inf, char *va);
int _setenv(inf_o *inf, char *va, char *val);
char **get_environ(inf_o *inf);
/*hist*/
int build_hist_list(inf_o *inf, char *buff, int lcount);
int renumber_hist(inf_o *inf);
char *get_hist_file(inf_o *inf);
int write_history(inf_o *inf);
int read_history(inf_o *inf);
/*alot*/
int is_chain(inf_o *inf, char *buff, size_t *ptr);
void check_chain(inf_o *inf, char *buff, size_t *ptr, size_t i, size_t l);
int replace_string(char **o, char *n);
int replace_alias(inf_o *inf);
int replace_vars(inf_o *inf);
#endif
