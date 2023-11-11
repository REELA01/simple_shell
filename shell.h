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

#define R_BUF_SIZE 1024
#define W_BUF_SIZE 1024
#define BUF_FL -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

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
	char *arg;
	char **argv;
	char *path;
	char *fname;
	char **environ;
	char **cmd_buf;
	int argc;
	int err_num;
	int linecount_flag;
	int env_changed;
	int status;
	int cmd_buf_type;
	int readfd;
	int histcount;
	unsigned int line_count;
	lis_t *env;
	lis_t *history;
	lis_t *alias;
} inf_o;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* path.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

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
/* builtin_emulators.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* builtin_emulators2.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* getline.c module */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* env2.c module */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
/* file_io_functions.c*/
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* chain.c */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
