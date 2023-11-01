#ifndef __SHELL__
#define __SHELL__

/* header files */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/* macros */

#define BUFFER_SIZE 1024
#define TOKEN_SIZE 64
#define DELIMITERS           \
	{                        \
		";", "#", "&&", "||" \
	}

/* Function Prototypes */

void shell(void);
char *_getline(void);
char **parse_line(char *);
int _getchar(void);
void *_realloc(void *, unsigned int, unsigned int);
char *_memcpy(char *, char *, unsigned int);
char **strtow(char *);
int _strlen(char *);

#endif
