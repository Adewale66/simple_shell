#include "shell.h"

/**
 * shell - Entry point for the shell
 * @filename: name of the file
 * Return: EXIT_STATUS
 */

int shell(char *filename)
{
	char *line;
	int stat_code = 0;
	int multiple = -1;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDIN_FILENO, "$ ", 2);
		line = read_line();
		if (line == NULL && isatty(STDIN_FILENO))
			continue;
		else if (line == NULL && !isatty(STDIN_FILENO))
			return (stat_code);
		multiple = check_for_multiple(line);
		if (multiple > 0)
			stat_code = handle_multiple(line, multiple, filename, stat_code);
		else if (multiple == 0)
			stat_code = 0;
		else
			stat_code = parse_line(line, filename, stat_code);
	}
}
