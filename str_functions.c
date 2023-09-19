#include "shell.h"

/**
 * _putchar_error - writes the character c to stderror
 * @c: The character to print
 * Return: On success 1 or -1 on error
 */
int _putchar_error(char c)
{
	return (write(2, &c, 1));
}

/**
 * _puts_error - Prints a string in stderror.
 * @str: string to be printed.
 * Return: Nothing
 */
void _puts_error(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		write(2, &str[i], 1);
}

/**
 * _puts - Prints a string in stdout.
 * @str: string to be printed.
 * Return: Nothing
 */
void _puts(char *str)
{
	int i;

	for (i = 0; str[i] != '\0'; i++)
		write(1, &str[i], 1);
}

/**
 * print_number - print an int numbers.
 * @n: the given number
 * Return: Nothing
 */
void print_number(int n)
{
	int i, digit, power;
	unsigned int temp, numchar, number;

	digit = 1;
	if (n < 0)
	{
		_putchar_error('-');
		temp = -n;
	}
	else
		temp = n;

	number = temp;
	while (number >= 10)
	{
		number = number / 10;
		digit++;
	}

	i = 1;
	power = 1;
	while (i < digit)
	{
		power = power * 10;
		i++;
	}
	while (power >= 1)
	{
		numchar = (temp / power) % 10;
		_putchar_error(numchar + '0');
		power = power / 10;
	}
}

/**
 * _split - split the string to seperates word
 * @str: the given string
 * @delim: seperators
 * Return: array of strings
 */
char **_split(char *str, char *delim)
{
	char **args;
	size_t i = 0;
	size_t len = args_counter(str, delim);
	char *res = strtok(str, delim);

	args = malloc(sizeof(char *) * (len + 1));
	if (!args)
		get_error("malloc", 1);

	while (i < len)
	{
		args[i] = _strdup(res);
		if (!args[i++])
			get_error("malloc", 1);
		res = strtok(NULL, delim);
	}
	args[i] = NULL;

	return (args);
}
