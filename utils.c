#include "utils.h"

/**
 * _getchar - reads a character from stdin
 * Return: character
 */

int _getchar(void)
{
	char c;

	if (read(STDIN_FILENO, &c, 1) == 1)
		return (c);
	else
		return (EOF);
}

/**
 * _realloc - reallocates a memory block
 * @old_size: old size of memory block
 * @new_size: new size of memory block
 * @ptr: pointer to memory block
 * Return: void pointer
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_block;

	if (new_size == old_size)
		return (ptr);
	if (ptr != NULL && new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));

	new_block = malloc(new_size);
	if (new_block == NULL)
		return (NULL);
	_memcpy(new_block, ptr, old_size);
	free(ptr);
	return (new_block);
}

/**
 * _memcpy -  function that copies memory area.
 * @dest: destination parameter
 * @src: source parameter
 * @n: buffer size to copy
 *
 * Return: pointer to dest
 */

char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i = 0;

	for (; i < n; i++)
		dest[i] = src[i];

	return (dest);
}

/**
 * _strtok -  function that splits a string into tokens
 * @str: string to split
 * @delim: delimiter
 * Return: pointer to string
 */

char *_strtok(char *str, const char *delim)
{
	static char *string_backup;
	char *r;

	if (str == NULL)
		str = string_backup;
	if (str == NULL)
		return (NULL);

	while (1)
	{
		if (is_delim(*str, delim))
		{
			str++;
			continue;
		}
		if (*str == '\0')
			return (NULL);
		break;
	}
	r = str;
	while (1)
	{
		if (*str == '\0')
		{
			string_backup = str;
			return (r);
		}
		if (is_delim(*str, delim))
		{
			*str = '\0';
			string_backup = str + 1;
			return (r);
		}
		str++;
	}
}

/**
 * is_delim -  function that checks if a character is a delimiter
 * @c: character to check
 * @delim: delimiter
 * Return: 1 if true, 0 if false
 */

unsigned int is_delim(char c, const char *delim)
{
	int i = 0;

	while (delim[i] != '\0')
	{
		if (c == delim[i])
			return (1);
		i++;
	}
	return (0);
}
