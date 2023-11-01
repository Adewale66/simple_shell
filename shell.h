#ifndef __SHELL__
#define __SHELL__

/* header files */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* macros */
#define BUFFER_SIZE 1024

/* Function Prototypes */
void shell(void);
char *_getline(void);
int _getchar(void);

#endif
