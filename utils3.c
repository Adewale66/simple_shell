#include "shell.h"

/**
 * _atoi - convert a string to an integer.
 * @s: string to convert
 * Return: int
 */
int _atoi(char *s)
{
	int i, d, n, len, f, digit;

	i = 0;
	d = 0;
	n = 0;
	len = 0;
	f = 0;
	digit = 0;

	while (s[len] != '\0')
		len++;

	while (i < len && f == 0)
	{
		if (s[i] == '-')
			++d;
		if (s[i] >= '0' && s[i] <= '9')
		{
			digit = s[i] - '0';
			if (d % 2)
				digit = -digit;
			n = n * 10 + digit;
			f = 1;
			if (s[i + 1] < '0' || s[i + 1] > '9')
				break;
			f = 0;
		}
		i++;
	}

	if (f == 0)
		return (-1);
	return (n);
}

/**
 * convert_unsigned_int - helper function to convert int to string
 * @num: number to convert
 * Return: char pointer (string)
 */

char *convert_unsigned_int(unsigned int num)
{
	int length, i;
	char *str;
	unsigned long int temp;

	length = 1;

	temp = num;
	while (temp /= 10)
		length++;

	str = (char *)malloc(length + 1);

	if (str == NULL)
		return (NULL);

	i = length - 1;
	str[i + 1] = '\0';

	do {
		str[i--] = num % 10 + '0';
		num /= 10;
	} while (num > 0);

	return (str);
}

/**
 * replace_string - replaces all occurrences of a substring with another
 * @original: original string
 * @pattern: substring to replace
 * @replacement: substring to replace with
 * Return: char *
 */
char *replace_string(char *original, char *pattern, char *replacement)
{
	char *result;
	char *ins;
	char *tmp;
	int len_pattern = _strlen(pattern);
	int le_rep = _strlen(replacement);
	int len_original = _strlen(original);
	int count = 0;
	int len_until_pattern;

	for (ins = original; (tmp = strstr(ins, pattern)); ++count)
	{
		ins = tmp + len_pattern;
	}

	result = (char *)malloc(len_original + (le_rep - len_pattern) * count + 1);

	if (!result)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	ins = result;
	while (count--)
	{
		tmp = strstr(original, pattern);
		len_until_pattern = tmp - original;
		_strncpy(ins, original, len_until_pattern);
		ins += len_until_pattern;
		_strcpy(ins, replacement);
		ins += le_rep;
		original = tmp + len_pattern;
	}
	_strcpy(ins, original);

	return (result);
}

/**
 * _strncpy - copies a string
 * @dest: destination string
 * @src: source string
 * @n: number of bytes
 * Return: char *
 */
char *_strncpy(char *dest, char *src, int n)
{
	{
		int i;

		for (i = 0; i < n && src[i] != '\0'; i++)
			dest[i] = src[i];
		for (; i < n; i++)
			dest[i] = '\0';

		return (dest);
	}
}
