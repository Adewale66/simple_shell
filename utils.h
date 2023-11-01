#ifndef __UTIL__
#define __UTIL__

/* Header files */

#include "shell.h"

/* macros */

#define BUFFER_SIZE 1024
#define TOKEN_SIZE 64
#define DELIMITERS           \
	{                        \
		";", "#", "&&", "||" \
	}

/* Function Prototypes */

int _getchar(void);
void *_realloc(void *, unsigned int, unsigned int);
char *_memcpy(char *, char *, unsigned int);
char **strtow(char *);
int _strlen(char *);

#endif
