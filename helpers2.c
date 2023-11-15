#include "shell.h"

/**
 * handle_comment - handles when a comment is passed
 * @line: pointer to line
 * @filename: pointer to filename
 * @status_code: status of shell
 * Return: int
 */
int handle_comment(char *line, char *filename, int status_code)
{
	char **command = strtow(line, '#');
	int status;

	if (command == NULL)
		return (0);
	status = parse_line(command[0], filename, status_code);
	return (status);
}

/**
 * handle_semi - handles when a semi is passed
 * @line: pointer to line
 * @filename: pointer to filename
 * @status: status of shell
 * Return: int
 */
int handle_semi(char *line, char *filename, int status)
{
	char **command = strtow(line, ';');
	int status_code;
	int i = 0;

	if (command == NULL)
		return (0);

	while (command[i])
		status_code = parse_line(command[i++], filename, status);
	return (status_code);
}

/**
 * handle_or - handles when an or is passed
 * @line: pointer to line
 * @filename: pointer to filename
 * @status: status of shell
 * Return: int
 */

int handle_or(char *line, char *filename, int status)
{
	char *replace_or;
	char **command;
	int status_code, i = 0;

	replace_or = replace_string(line, "||", "|");
	if (replace_or == NULL)
		return (0);
	command = strtow(replace_or, '|');
	if (command == NULL)
		return (0);

	while (command[i])
	{
		status_code = parse_line(command[i], filename, status);
		if (status_code == 0)
			break;
		i++;
	}
	free(replace_or);
	free(command);
	return (status_code);
}

/**
 * handle_and - handles when an and is passed
 * @line: pointer to line
 * @filename: pointer to filename
 * @status: status of shell
 * Return: int
 */
int handle_and(char *line, char *filename, int status)
{
	char *replace_and;
	char **command;
	int status_code, i = 0;

	replace_and = replace_string(line, "&&", "&");
	if (replace_and == NULL)
		return (0);
	command = strtow(replace_and, '&');
	if (command == NULL)
		return (0);
	while (command[i])
	{
		status_code = parse_line(command[i], filename, status);
		if (status_code != 0)
			break;
		i++;
	}
	free(replace_and);
	free(command);
	return (status_code);
}
