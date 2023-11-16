#include "shell.h"

/**
 * exit_shell - exits the shell
 * @s: array of strings
 * @filename: names of strings passed via command line
 * @stat: status code
 * @env: environment
 * @line: line
 * Return: 0
 */
int exit_shell(char **s, char *filename, int stat, char *env, char *line)
{
	int status;

	if (s[1] != NULL)
	{
		status = _atoi(s[1]);
		if (status < 0)
			exit_error_handler(filename, s, 2, env, line);
	}
	else
		status = stat;
	free_strings(2, env, line);
	free_array(s);
	exit(status);
}

/**
 * shell_env - prints the environment
 * Return: 0
 */
int shell_env(void)
{
	pid_t pid;
	char *file = "env.sh";
	int status;

	create_file();

	char *args[] = {"env", NULL};

	pid = fork();
	if (pid == 0)
	{

		if (execve(file, args, environ) == -1)
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
		wait(&status);
	return (status);
}

/**
 * shell_echo - handles echo command
 * @line: argument passed to echo
 * Return: int
 */

int shell_echo(char **line)
{
	int i = 1;

	while (line[i])
	{
		write(STDOUT_FILENO, line[i], _strlen(line[i]));
		if (line[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	write(STDOUT_FILENO, "\n", 1);

	return (0);
}

/**
 * _setenv - sets an environment variable
 * @name: name of environment variable
 * @value: value of environment variable
 * @overwrite: overwrite flag
 * Return: 0, -1 on failure
 */
int _setenv(char *name, char *value, int overwrite)
{
	int name_exists = 0, i = 0, fount_idx;
	char **env_name;

	if (!name || !value)
		return (-1);
	if (!overwrite)
		overwrite = 1;
	while (environ[i])
	{
		env_name = strtow(environ[i], '=');
		if (!env_name)
			return (-1);
		if (_strcmp(env_name[0], name) == 0)
		{
			name_exists = 1;
			fount_idx = i;
			free_array(env_name);
			break;
		}
		free_array(env_name);
		i++;
	}
	if (name_exists)
	{
		if (overwrite)
			return (update_env(name, value, fount_idx));
		return (0);
	}
	return (create_env(name, value, i));
}

/**
 * _unsetenv - removes an environment variable
 * @name: name of environment variable
 * Return: 0, -1 on failure
 */

int _unsetenv(char *name)
{
	int i = 0, j = 0, name_exists = 0;
	char **env;

	if (!name)
		return (-1);
	while (environ[i])
		if (_strstr(environ[i++], name))
		{
			name_exists = 1;
			break;
		}
	if (!name_exists)
		return (0);
	env = malloc(sizeof(char *) * i);
	if (!env)
		return (-1);
	i = 0;
	while (environ[i])
	{
		if (!_strstr(environ[i], name))
		{
			env[j] = _strdup(environ[i]);
			if (!env[j])
			{
				while (j >= 0)
					free(env[j--]);
				free(env);
				return (-1);
			}
			j++;
		}
		i++;
	}
	env[j] = NULL;
	environ = env;
	return (0);
}
