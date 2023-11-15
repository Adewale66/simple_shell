#include "shell.h"

/**
 * main - Entry point
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: EXIT_STATUS
 */

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		return (handle_file(argv[1], argv[0]));
	}
	else
		return (shell(argv[0]));
}
