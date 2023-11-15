#include "shell.h"

/**
 * _strstr - function that locates a substring.
 * @hay: char pointer
 * @needle: char pointer
 *
 * Return: int
 */
int _strstr(char *hay, const char *needle)
{
	while (*hay)
	{
		char *h = hay;
		const char *n = needle;

		while (*h && *n && *h == *n)
		{
			h++;
			n++;
		}

		if (!*n)
			return (1);
		hay++;
	}
	return (0);
}

/**
 * _strcmp - compare two strings
 * @s1: first string parameter
 * @s2: second string parameter
 * Return: int
 */
int _strcmp(const char *s1, char *s2)
{
	int len = 0;

	while (s1[len] != '\0' && s1[len] == s2[len])
		len++;
	return (s1[len] - s2[len]);
}

/**
 * _strcat -  concatenates two strings.
 * @dest: destination string parameter
 * @src: source string parameter
 * Return: char *
 */
char *_strcat(char *dest, char *src)
{
	int len = 0, lenSrc = 0;

	while (dest[len] != '\0')
		len++;

	while (src[lenSrc] != '\0')
	{
		dest[len] = src[lenSrc];
		len++;
		lenSrc++;
	}
	dest[len] = '\0';
	return (dest);
}

/**
 * _strdup - returns a pointer to newly allocated space in memory
 * @str: char pointer
 * Return: char pointer
 */
char *_strdup(char *str)
{
	char *t;
	int len = 0, i = 0;

	if (str == NULL)
		return (NULL);

	while (str[len] != '\0')
		len++;
	t = (char *)malloc(len + 1);
	if (t == NULL)
		return (NULL);

	for (; i < len; i++)
		t[i] = str[i];
	t[len] = '\0';
	return (t);
}

/**
 * _strcpy -  copies the string pointed to by src
 * @dest : destination parameter
 * @src: source parameter
 * Return: pointer
 */
char *_strcpy(char *dest, char *src)
{
	int len = 0, i = 0;

	while (src[len] != '\0')
		len++;

	for (; i <= len; i++)
		dest[i] = src[i];
	return (dest);
}
