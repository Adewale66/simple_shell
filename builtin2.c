#include "shell.h"

/**
 * change_dir - changes the current working directory
 * @path: path to change to (NULL if no path)
 * @filename: name of the file
 * Return: 0 on success, -1 on failure
 */

int change_dir(char *path, char *filename)
{
	char *oldpwd = _getenv("OLDPWD");
	char *pwd = getcwd(NULL, 0), *home = _getenv("HOME");
	int check;

	if (path == NULL)
	{
		check = chdir(home);
		if (check == -1)
		{
			cd_error_handler(filename, home);
			return (-1);
		}
	}
	else if (_strcmp(path, "-") == 0)
	{
		check = chdir(oldpwd);
		if (check == -1)
		{
			cd_error_handler(filename, oldpwd);
			return (-1);
		}
	}
	else
	{
		check = chdir(path);
		if (check == -1)
		{
			cd_error_handler(filename, path);
			return (-1);
		}
	}
	_setenv("OLDPWD", pwd, 1);
	_setenv("PWD", getcwd(NULL, 0), 1);
	free(pwd);
	return (0);
}
