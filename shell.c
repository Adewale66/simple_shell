#include "shell.h"

/**
 * shell - Starts the shell
 * Return: void
 */

void shell(void)
{
	char *line;
	char **args;
	int status;

	do
	{
		write(STDOUT_FILENO, "$ ", 3);
		line = _getline();
		args = parse_line(line);
		status = execute(args);

		free(line);
		free(args);
	} while (status);
}
