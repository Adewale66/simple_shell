#include "shell.h"

/**
 * create_path - creats string
 * @full_command: pointer to string
 * @current: pointer to current directory
 * @entry: pointer to entry
 * Return: void
 */

void create_path(char *full_command, dir_node *current, struct dirent *entry)
{
	_strcpy(full_command, current->dir);
	_strcat(full_command, "/");
	_strcat(full_command, entry->d_name);
}

/**
 * __strstr - function that locates a substring.
 * @hay: char pointer
 * @needle: char pointer
 *
 * Return: pointer
 */

char *__strstr(char *hay, char *needle)
{
	while (*hay)
	{
		char *h = hay;
		char *n = needle;

		while (*h && *n && *h == *n)
		{
			h++;
			n++;
		}

		if (!*n)
			return (hay);
		hay++;
	}
	return ('\0');
}

/**
 * free_handler - handles errors
 * @fn: name of file
 * @a: array of strings
 * @h: head of linked list
 * @e: pointer to environment
 * @l: pointer to line
 * @pd: array of strings
 * Return: 127
 */

int free_handler(char *fn, char **a, char **pd, char *l, char *e, dir_node *h)
{
	path_error_handler(fn, a[0]);
	free_strings(2, e, l);
	free_arr_list(a, h);
	free(pd);
	return (127);
}

/**
 * create_file - creates env file
 * Return: void
 */
void create_file()
{
	char *file = "env.sh";
	int fd;
	ssize_t bytes;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	bytes = write(fd, "#!/bin/sh\nprintenv", 18);

	if (bytes == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
	close(fd);
}
