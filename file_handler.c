#include "shell.h"

/**
 * handle_file - handles file
 * @filename: pointer to filename
 * @program_name: pointer to program name
 * Return: int
 */

int handle_file(char *filename, char *program_name)
{
	int file_access;

	file_access = access(filename, F_OK | R_OK);
	if (file_access == 0)
		return (parse_file(filename, program_name));
	write(STDERR_FILENO, program_name, _strlen(program_name));
	write(STDERR_FILENO, ": 0: cannot open ", 17);
	write(STDERR_FILENO, filename, _strlen(filename));
	write(STDERR_FILENO, ": No such file", 14);
	write(STDERR_FILENO, "\n", 1);

	return (2);
}

/**
 * parse_file - parses file
 * @filename: pointer to filename
 * @program_name: pointer to program name
 * Return: int
 */

int parse_file(char *filename, char *program_name)
{
	char **commands;
	char line[MAX_LINE];
	int i = 0;
	static int status;
	int prev = 0;
	ssize_t bytes;
	int read_file = open(filename, O_RDONLY);

	if (read_file == -1)
		return (0);

	bytes = read(read_file, line, MAX_LINE);
	if (bytes == -1)
		return (0);
	line[bytes] = '\0';

	commands = strtow(line, '\n');
	if (commands == NULL)
		return (0);
	while (commands[i])
	{
		status = parse_line(commands[i++], program_name, prev);
		prev = status;
	}
	free(commands);
	close(read_file);
	return (status);
}
