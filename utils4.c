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
 * _strstr - function that locates a substring.
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
