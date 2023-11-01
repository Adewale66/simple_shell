#ifndef __SHELL__
#define __SHELL__

/* header files */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

/* Function Prototypes */

void shell(void);
char *_getline(void);
char **parse_line(char *);

#endif
