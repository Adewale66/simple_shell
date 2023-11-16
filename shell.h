#ifndef __SHELL__
#define __SHELL__

/* Libraries */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdarg.h>

/* Global variables */
extern char **environ;

/* Macros */
#define BUFFER_SIZE 100
#define MAX_LINE 1024

/**
 * struct node - singly linked list
 * @dir: string - (malloc'ed string)
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct node
{

	char *dir;
	struct node *next;
} dir_node;

/* Shell prototypes */

int shell(char *);
char *read_line(void);
int parse_line(char *line, char *, int);
int execute(char **args, char *command);
int check_for_multiple(char *args);
int handle_multiple(char *, int, char *, int);
int handle_comment(char *line, char *filename, int status_code);
int handle_semi(char *line, char *filename, int status);
int handle_and(char *line, char *filename, int status);
int handle_or(char *line, char *filename, int status);

/* fucntion prototypes for builtin*/

int exit_shell(char **, char *, int, char *, char *);
int shell_env(void);
int shell_echo(char **arg);
int check_for_builtin(char **args, char *, int, char *, char *);
int change_dir(char *path, char *filename);
int _setenv(char *name, char *value, int overwrite);
int _unsetenv(char *name);

/* helper function protoypes*/

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **strtow(char *str, char delim);
int _strlen(char *s);
void free_array(char **);
int _strstr(char *hay, const char *needle);
char *_getenv(char *name);
int _strcmp(const char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
int _atoi(char *s);
char *_strdup(char *str);
char *convert_unsigned_int(unsigned int num);
char *_strncpy(char *dest, char *src, int n);
char *replace_string(char *original, char *pattern, char *replacement);
void free_arr_list(char **arr, dir_node *list);
void free_strings(int count, ...);
void create_path(char *full_command, dir_node *current, struct dirent *entry);
int update_env(char *name, char *value, int fount_idx);
int create_env(char *name, char *value, int size);
char *__strstr(char *hay, char *needle);
int free_handler(char *fn, char **a, char **pd, char *l, char *e, dir_node *h);

/** linked list functions */

void insertNode(dir_node **head, char *dir);
dir_node *create_node(char *dir);
void free_list(dir_node *head);
char *check_path(dir_node *head, char *args);
char *check_for_access(char *args);

/* file handlers*/
int handle_file(char *filename, char *program_name);
int parse_file(char *filename, char *program_name);
void create_file();

/* error handlers*/
void path_error_handler(char *filename, char *command);
void exit_error_handler(char *filename, char **command, int status, char *env, char *li);
void cd_error_handler(char *filename, char *command);

#endif
