#ifndef SHELL_H
#define SHELL_H

/* libraries we need */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <fcntl.h>

/* buffers we need */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining functions*/
#define CMD_NORM    0
#define CMD_OR      1
#define CMD_AND     2
#define CMD_CHAIN   3

/* for convrt num function */
#define CONVERT_LOWERCASE    1
#define CONVERT_UNSIGNED     2

/* get line system call */
#define USE_GETLINE 0
#define USE_STRTOK  0

/* simple shell history file*/
#define HIST_FILE ".simple_shell_history"
#define HIST_MAX  4096

extern char **environ;

/**
 *struct liststr - linked lists
 * @num: the num field
 * @str: string
 * @next: pointing to next node
*/
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;



/**
 *struct information - args pass to functions to use it
 * @arg: arguments
 * @argv: argument vector
 * @path: str path for current cmd
 * @line_count: err count
 * @argc: arguments counter
 * @err_num: err code for exit()s
 * @histcount: history lines counter
 * @readfd: read line input
 * @cmd_buf_type: ||, &&, ;
 * @cmd_buf: address of pointer
 * @status: the return status
 * @env_changed: if environ was changed
 * @alias: alias node
 * @history: history node
 * @environ: custum modified copy of environ
 * @env: linked list local cpy of environ
 * @fname: programm filename
 * @linecount_flag: if on count this line of input
*/

typedef struct information
{
	char *arg;
	char **argv;
	char *path;
	char argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* ptr to cmd ; chain buffer, memory mangment*/
	int cmd_buf_type;
	int readfd;
	int histcount;
} import_t;

#define IMPORT_INIT {NULL, NULL, NULL, 0, 0, 0, 0, \
	NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

/**
 *struct builtin - builtin string and related functions
 * @type: the builtin cmd flag
 * @func: the function of all
*/
typedef struct builtin
{
	char *type;
	int (*func)(import_t *);
} biltin_table;

/* PROTOTYPES OF ALL FUNCTIONS */

/* dealing with srting */
/* first file */
int _strlen(char *);
int _strcmp(char  *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* seconed file */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* third file */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* fourth file */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* function that deal with a memory */
/* the first file */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
/* the seconed file */
int bfree(void **);

/* function we need during the process*/
/* first file */
int interactive(import_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

/* the seconed file */
int _errtoi(char *);
void print_error(import_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comment(char *);

/* linked lists that we need */
/* the first file */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* the second file */
size_t list_len(const list_t *);
char **list_to_string(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

/* deling with errors */
/* the error file*/
void _eputs(char *);
int _eputchar(char);
int _putfd(char ch, int fd);
int _putsfd(char *strs, int fd);

/* import struct function */
void clear_import(import_t *);
void set_import(import_t *, char **);
void free_import(import_t *, int);

/* making a enviroment */
/* the first file */
char *_getenv(import_t *, const char *);
int _myenv(import_t *);
int _mysetenv(import_t *);
int _myunsetenv(import_t *);
int populate_env_list(import_t *);

/* the seconed file */
char **get_environ(import_t *);
int _unsetenv(import_t *, char *);
int _setenv(import_t *, char *, char *);

/* builtin elminators */
/* the first file*/
int _myexit(import_t *);
int _mycd(import_t *);
int _myhelp(import_t *);

/* the second file*/
int _myhistory(import_t *);
int _myalias(import_t *);

/* handle the path */
int is_cmd(import_t *, char *);
char *find_path(import_t *, char *, char *);
char *dup_chars(char *, int, int);

/* chainig files */
int is_chain(import_t *, char *, size_t *);
int replace_string(char **, char *);
int replace_vars(import_t *);
int replace_alias(import_t *);
void check_chain(import_t *, char *, size_t *, size_t, size_t);

/* file.io functions*/
char *get_history_file(import_t *import);
int write_history(import_t *import);
int read_history(import_t *import);
int build_history_list(import_t *import, char *buf, int linecount);
int renumber_history(import_t *import);

/* loopsh files*/
int loopsh(char *);

/* getline module*/
ssize_t get_input(import_t *);
int _getline(import_t *, char **, size_t *);
void signhandler(int);

/* hsh */
int hsh(import_t *, char **);
int find_builtin(import_t *);
void find_cmd(import_t *);
void fork_cmd(import_t *);

#endif
