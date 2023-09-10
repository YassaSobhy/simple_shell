#ifndef SIMPLE_H
#define SIMPLE_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

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
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguments to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguments
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@lineCount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histCount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int lineCount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory management */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histCount;
} info_t;

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



/* err_str_func.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* str_func_1.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* str_func_2.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* str_func_3.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* str_func_4.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* builtin_func1.c */
int _exit_function(info_t *);
int _cd_function(info_t *);
int _help_function(info_t *);

/* builtin_func2.c */
int _history_func(info_t *);
int _alias_func(info_t *);

/* getline_func.c module */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void siginalHandler(int);

/* info_func.c module */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* env_func1.c module */
char *_get_env(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_linked_list(info_t *);

/* env_func2.c module */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* file_io_func.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int lineCount);
int renumber_history(info_t *info);

/*sh_funs.c*/
int main_shll(info_t *, char **);
int srch_bltin(info_t *);
void fcmd(info_t *);
void cmdfrk(info_t *);

/* funs_pth.c */
int execmd(info_t *, char *);
char *chdupl(char *, int, int);
char *pthserch(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* funsmem_1.c */
char *_fillmemory(char *, char, unsigned int);
void rreset(char **);
void *_redef(void *, unsigned int, unsigned int);

/*funsmem_2.c */
int freemem(void **);

/* funsdef_1.c */
int mode_detect(info_t *);
int checkspace(char, char *);
int _checkalpha(int);
int _contint(char *);

/* funsdef_2.c */
int _strtint(char *);
void errordis(info_t *, char *);
int deciprint(int, int);
char *numconv(long int, int, int);
void remocomnt(char *);

/* strtab_1.c module */
list_t *defnode(list_t **, const char *, int);
list_t *nodetend(list_t **, const char *, int);
size_t listdistr(const list_t *);
int de_spec_node(list_t **, unsigned int);
void redflst(list_t **);

/* strtab_2.c module */
size_t lenlst(const list_t *);
char **lsttstr(list_t *);
size_t lstdis(const list_t *);
list_t *stndwth(list_t *, char *, char);
ssize_t recndix(list_t *, list_t *);

/*links.c */
int testch(info_t *, char *, size_t *);
void shchain(info_t *, char *, size_t *, size_t, size_t);
int chalias(info_t *);
int vars_ch(info_t *);
int restring(char **, char *);
#endif
