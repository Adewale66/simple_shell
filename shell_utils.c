#include "shell.h"

/**
 * read_line - reads a line from stdin
 * Return: pointer to the line
 */

char *read_line(void)
{
	char *line_read = NULL;
	size_t buffer_size = 0;

	if (getline(&line_read, &buffer_size, stdin) == -1)
	{
		if (feof(stdin))
			return (NULL);

		perror("read error");
		exit(EXIT_FAILURE);
	}
	line_read[_strlen(line_read) - 1] = '\0';
	return (line_read);
}

/**
 * parse_line - parses a line into an array of strings
 * @line: pointer to the line
 * @filename: name of file
 * @status_code: status code of shell
 * Return: array of strings
 */

int parse_line(char *line, char *filename, int status_code)
{
	char *env = _getenv("PATH"), *cmd, **path_dirs, **args;
	dir_node *head = NULL;
	int i = 0, status, builtin_check;

	args = strtow(line, ' ');
	if (!args)
	{
		free_strings(2, env, line);
		return (0);
	}
	builtin_check = check_for_builtin(args, filename, status_code, env, line);
	if (builtin_check != -2)
	{
		free_array(args);
		free_strings(2, env, line);
		return (builtin_check);
	}
	path_dirs = strtow(env, ':');
	if (path_dirs == NULL)
	{
		status = 127;
		if (args[0][0] == '/')
			status = execute(args, args[0]);
		else
			path_error_handler(filename, args[0]);
		free_strings(2, env, line);
		free_array(args);
		return (status);
	}
	while (path_dirs[i])
		insertNode(&head, path_dirs[i++]);
	cmd = check_path(head, args[0]);
	if (cmd == NULL)
		return (free_handler(filename, args, path_dirs, line, env, head));
	status = execute(args, cmd);
	free_arr_list(args, head);
	free_strings(3, env, line, cmd);
	free(path_dirs);
	return (status);
}

/**
 * execute - executes a command
 * @args: array of arguments
 * @command: command to execute
 * Return: 1
 */

int execute(char **args, char *command)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{

		if (execve(command, args, environ) == -1)
		{
			perror("sh");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{

		perror("fork failed");
		status = -1;
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
	}
	return (status);
}

/**
 * check_for_multiple - checks for multiple commands
 * @line: pointer to the line
 * Return: 1,2,3,4 if multiple commands, 0 otherwise
 */

int check_for_multiple(char *line)
{
	int type = -1;
	int i = 0;

	if (!line)
		return (0);

	for (; line[i]; i++)
	{
		if (line[i] == '#' && i != 0 && (line[i + 1] == ' ' || line[i - 1] == ' '))
		{
			type = 4;
			break;
		}
		if (line[i] == ';')
		{
			type = 1;
			break;
		}
		if (line[i] == '&' && line[i + 1] == '&')
		{
			type = 2;
			break;
		}
		if (line[i] == '|' && line[i + 1] == '|')
		{
			type = 3;
			break;
		}
	}
	return (type);
}

/**
 * handle_multiple - handles multiple commands
 * @line: pointer to the line
 * @type: type of command
 * @filename: name of file
 * @status: status of shell
 * Return: 0
 */

int handle_multiple(char *line, int type, char *filename, int status)
{
	if (type == 4)
		return (handle_comment(line, filename, status));
	if (type == 3)
		return (handle_or(line, filename, status));
	if (type == 2)
		return (handle_and(line, filename, status));
	return (handle_semi(line, filename, status));
}
