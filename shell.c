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

	if (!isatty(STDIN_FILENO))
	{
		while ((line = read_line()))
		{
			multiple = check_for_multiple(line);
			if (multiple > 0)
				stat_code = handle_multiple(line, multiple, filename, stat_code);
			else if (multiple == 0)
				stat_code = 0;
			else
				stat_code = parse_line(line, filename, stat_code);
		}
		return (stat_code);
	}
	else
	{
		while (1)
		{
			write(STDIN_FILENO, "$ ", 2);
			line = read_line();
			multiple = check_for_multiple(line);
			if (multiple > 0)
				stat_code = handle_multiple(line, multiple, filename, stat_code);
			else if (multiple == 0)
				stat_code = 0;
			else
				stat_code = parse_line(line, filename, stat_code);
		}
	}
}
