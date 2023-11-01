#ifndef __UTIL__
#define __UTIL__

/* Header files */

#include "shell.h"

/* macros */

#define BUFFER_SIZE 1024
#define TOKEN_SIZE 64
#define DELIMETERS " \a\t\r\n"

/* Function Prototypes */

int _getchar(void);
void *_realloc(void *, unsigned int, unsigned int);
char *_memcpy(char *, char *, unsigned int);
char *_strtok(char *, const char *);
unsigned int is_delim(char, const char *);

#endif
