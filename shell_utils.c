#include "utils.h"

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
			buffer[index] = c;
		index++;
		if (index >= buffersize)
		{
			int oldsize = buffersize;

			buffersize += BUFFER_SIZE;
			buffer = _realloc(buffer, oldsize, buffersize);
			if (!buffer)
			{
				perror("Unable to allocate buffer");
				exit(EXIT_FAILURE);
			}
		}
	}
}

/**
 * parse_line - parses a line of input
 * @line: line of input
 * Return: array of tokens
 */

char **parse_line(char *line)
{
	char **tokens;

	if (line == NULL)
		return (NULL);
	tokens = strtow(line);
	return (tokens);
}
