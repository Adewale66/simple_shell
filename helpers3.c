#include "shell.h"

/**
 * free_strings - frees strings
 * @count: count of strings
 * Return: void
 */
void free_strings(int count, ...)
{
	va_list strings;
	int i;
	char *string;

	va_start(strings, count);
	for (i = 0; i < count; i++)
	{
		string = va_arg(strings, char *);
		free(string);
	}
	va_end(strings);
}

/**
 * free_arr_list - frees arrays and lists
 * @arr: array to free
 * @list: list to free
 * Return: void
 */
void free_arr_list(char **arr, dir_node *list)
{
	free_array(arr);
	free_list(list);
}

/**
 * update_env - updates env variable
 * @name: name of env variable
 * @value: value of env variable
 * @fount_idx: index of env variable
 * Return: 0, -1 on failure
 */

int update_env(char *name, char *value, int fount_idx)
{
	int i = 0;
	char **env;

	while (environ[i])
		i++;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (-1);
	i = 0;
	while (environ[i])
	{
		if (i == fount_idx)
		{
			env[fount_idx] = malloc(_strlen(name) + _strlen(value) + 2);
			if (!env[fount_idx])
			{
				free_array(env);
				return (-1);
			}
			_strcpy(env[fount_idx], name);
			_strcat(env[fount_idx], "=");
			_strcat(env[fount_idx], value);
			i++;
			continue;
		}
		env[i] = _strdup(environ[i]);
		if (!env[i])
		{
			free_array(env);
			return (-1);
		}
		i++;
	}
	env[i] = NULL;
	environ = env;
	return (0);
}

/**
 * create_env - creates env variable
 * @name: name of env variable
 * @value: value of env variable
 * @size: size of env variable
 * Return: 0, -1 on failure
 */

int create_env(char *name, char *value, int size)
{
	char **env;
	int i = size;

	env = malloc(sizeof(char *) * (i + 2));
	if (!env)
		return (-1);
	i = 0;
	while (environ[i])
	{
		env[i] = _strdup(environ[i]);
		if (!env[i])
		{
			free_array(env);
			return (-1);
		}
		i++;
	}
	env[i] = malloc(_strlen(name) + _strlen(value) + 2);
	if (!env[i])
	{
		free_array(env);
		return (-1);
	}
	_strcpy(env[i], name);
	_strcat(env[i], "=");
	_strcat(env[i], value);
	env[i + 1] = NULL;
	environ = env;
	return (0);
}
