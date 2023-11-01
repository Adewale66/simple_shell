#include "shell.h"

/**
 * _getline - reads a line from stdin
 * Return: pointer to the line
 */

char *_getline(void)
{
	int buffersize = BUFFER_SIZE;
	int index = 0, c;
	char *buffer = (char *)malloc(sizeof(char) * buffersize);

	if (!buffer)
	{
		perror("Unable to allocate buffer");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		c = _getchar();
		if (c == EOF || c == '\n')
		{
			buffer[index] = '\0';
			return (buffer);
		}
		else
		{
			buffer[index] = c;
		}
		index++;
		if (index >= buffersize)
		{
			buffersize += BUFFER_SIZE;
			buffer = realloc(buffer, buffersize);
			if (!buffer)
			{
				perror("Unable to allocate buffer");
				exit(EXIT_FAILURE);
			}
		}
	}
}

/**
 * _getchar - reads a character from stdin
 * Return: character
 */

int _getchar(void)
{
	char c;

	if (read(STDIN_FILENO, &c, 1) == 1)
		return (c);
	else
		return (EOF);
}
