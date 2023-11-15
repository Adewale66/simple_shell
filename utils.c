#include "shell.h"

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
 * _strlen -  returns the length of a string.
 * @s: first parameter
 * Return: integer
 */
int _strlen(char *s)
{
	int length = 0;

	while (s[length] != '\0')
		length++;

	return (length);
}

/**
 * strtow - splits a string into words
 * @str: string to split
 * @delimiter: delimiter to split string
 * Return: pointer to cahr pointer
 */
char **strtow(char *str, char delimiter)
{
	char **t;
	int i = 0, l = 0, strle, j;

	if (str == NULL || *str == '\0')
		return (NULL);

	for (; str[i] != '\0'; i++)
		if (str[i] != delimiter)
			if (i - 1 < 0 || str[i - 1] == delimiter)
				l++;

	if (l == 0)
		return (NULL);

	t = (char **)malloc(sizeof(char *) * (l + 1));
	if (t == NULL)
		return (NULL);

	for (i = 0; i < l; i++)
	{
		while (*str == delimiter)
			str++;
		strle = 0;
		while (str[strle] != '\0' && str[strle] != delimiter)
			strle++;
		t[i] = (char *)malloc(sizeof(char) * (strle + 1));
		if (t[i] == NULL)
		{
			for (j = 0; j < i; j++)
				free(t[j]);
			free(t);
			return (NULL);
		}
		for (j = 0; j < strle; j++, str++)
			t[i][j] = *str;

		t[i][j] = '\0';
	}
	t[l] = NULL;
	return (t);
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
