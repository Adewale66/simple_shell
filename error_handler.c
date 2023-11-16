#include "shell.h"

/**
 * path_error_handler - handles errors for path
 * @filename: pointer to filename
 * @command: pointer to command
 * Return: void
 */

void path_error_handler(char *filename, char *command)
{
	write(STDERR_FILENO, filename, _strlen(filename));
	write(STDERR_FILENO, ": 1: ", 5);
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * exit_error_handler - handles errors for exit
 * @file: pointer to file
 * @cmd: pointer to command
 * @e: env
 * @li: line
 * @status: status code
 * Return: void
 */
void exit_error_handler(char *file, char **cmd, int status, char *e, char *li)
{
	write(STDERR_FILENO, file, _strlen(file));
	write(STDERR_FILENO, ": 1: exit: Illegal number: ", 27);
	write(STDERR_FILENO, cmd[1], _strlen(cmd[1]));
	write(STDERR_FILENO, "\n", 1);
	free_array(cmd);
	free_strings(2, e, li);
	exit(status);
}

/**
 * cd_error_handler - handles errors for cd
 * @filename: pointer to filename
 * @command: pointer to command
 * Return: void
 */
void cd_error_handler(char *filename, char *command)
{
	write(STDERR_FILENO, filename, _strlen(filename));
	write(STDERR_FILENO, ": 1: cd: can't cd to ", 21);
	write(STDERR_FILENO, command, _strlen(command));
	write(STDERR_FILENO, "\n", 1);
}
