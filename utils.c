#include "shell.h"

/**
 * _strlen - calc the length of the string
 * @s: The given string
 * Return: size_t
 */
size_t	_strlen(const char *s)
{
	size_t l = 0;

	while (s[l] != '\0')
		l++;
	return (l);
}

/**
 * is_built_in - check if the cmd built_in or not
 * @cmd: the given cmd
 * Return: true or false
 */
int is_built_in(char *cmd)
{
	return (_strcmp(cmd, "env") == 0 || _strcmp(cmd, "exit") == 0);
}

/**
 * get_error - prinrt the occurs error and exit
 * @str: the error source
 * @status: the status u wanna exit with
 * Return: Nothing
 */
void get_error(char *str, int status)
{
	perror(str);
	exit(status);
}

/**
 * free_array - free the two dimensional array
 * @array: two dimensional array
 * Return: Nothing
 */
void free_array(char **array)
{
	size_t i = 0;

	while (array[i])
		free(array[i++]);
	free(array);
}

/**
 * args_counter - count the words separated by the given charsets
 * @str: string
 * @charsets: string of separators
 * Return: the number of words exist
 */
int	args_counter(char *str, char *charsets)
{
	int	i = 0;
	int	count = 0;

	while (str[i])
	{
		while (str[i] && _strchr(charsets, str[i]))
			i++;
		if (str[i])
		{
			count++;
			i++;
		}
		while (str[i] && !_strchr(charsets, str[i]))
			i++;
	}
	return (count);
}
