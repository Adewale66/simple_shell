#include "shell.h"

/**
 * check_for_builtin - checks for builtins
 * @s: array of strings
 * @filename: arguments for file name
 * @stat: status code
 * Return: int
 */
int check_for_builtin(char **s, char *filename, int stat)
{
	int i = -2;

	if (_strcmp(s[0], "exit") == 0)
		exit_shell(s, filename, stat);
	if (_strcmp(s[0], "env") == 0)
		i = shell_env();
	if (_strcmp(s[0], "echo") == 0)
		i = shell_echo(s);
	if (_strcmp(s[0], "setenv") == 0)
	{
		if (s[2] == NULL)
			i = 0;
		else if (s[3] == NULL)
			i = _setenv(s[1], s[2], 1);
		else
			i = _setenv(s[1], s[2], _atoi(s[3]));
	}
	if (_strcmp(s[0], "unsetenv") == 0)
		i = _unsetenv(s[1]);
	if (_strcmp(s[0], "cd") == 0)
		i = change_dir(s[1], filename);
	return (i);
}

/**
 * _getenv - gets the value of an environment variable
 * @name: environment variable
 * Return: pointer to the value of the environment variable
 */
char *_getenv(char *name)
{
	int e, i = 0;
	char *r, **env_val;

	if (!name)
		return (NULL);
	while (environ[i])
	{
		env_val = strtow(environ[i], '=');
		if (env_val == NULL)
			return (NULL);
		e = _strcmp(env_val[0], name);
		if (e == 0)
		{
			r = _strdup(env_val[1]);
			if (r == NULL)
				return (NULL);
			return (r);
		}
		i++;
	}
	return (NULL);
}

/**
 * free_array - frees an array of strings
 * @arr: array to be freed
 */
void free_array(char **arr)
{
	int i = 0;

	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

/**
 * check_for_access - checks if a command exists
 * @command: command
 * Return: command
 */
char *check_for_access(char *command)
{
	int check;

	if (command[0] == '.' || command[0] == '/')
	{
		check = access(command, F_OK | X_OK);
		if (check == 0)
			return (command);
		else
			return (NULL);
	}
	return (command);
}

/**
 * check_path - checks if a command exists in a directory
 * @head: head of the list of directories
 * @cmd: command to check
 * Return: command
 */
char *check_path(dir_node *head, char *cmd)
{
	dir_node *current = head;
	struct dirent *entry;
	char *full_command = NULL, *file_exists;
	DIR *dir;
	int path;

	file_exists = check_for_access(cmd);
	if (file_exists == NULL)
		return (NULL);
	if (file_exists[0] == '.' || file_exists[0] == '/')
		return (_strdup(cmd));
	while (current != NULL)
	{
		dir = opendir(current->dir);
		if (dir == NULL)
		{
			current = current->next;
			continue;
		}
		while ((entry = readdir(dir)) != NULL)
		{
			if (_strcmp(cmd, entry->d_name) == 0)
			{
				path = _strlen(current->dir) + _strlen(entry->d_name) + 2;
				full_command = (char *)malloc(path);
				if (full_command == NULL)
				{
					perror("Could not allocate memory");
					closedir(dir);
					return (NULL);
				}
				create_path(full_command, current, entry);
				closedir(dir);
				return (full_command);
			}
		}
		closedir(dir);
		current = current->next;
	}
	return (NULL);
}
