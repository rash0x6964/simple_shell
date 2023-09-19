#include "shell.h"

/**
 * _strchr - find a char in string
 * @str: the given string
 * @c: the character
 * Return: the address of the char or NULL
 */
char *_strchr(char *str, char c)
{
	size_t i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (str + i);
		i++;
	}
	if (c != 0 && !str[i])
		return (0);
	return (str + i);
}

/**
 * _strdup - allocate a new string
 * @s1: the given string u want to allocate
 * Return: pointer to the string or NULL on error
 */
char *_strdup(char *s1)
{
	char	*ptr;

	ptr = malloc((_strlen(s1) + 1) * sizeof(char));
	if (!ptr)
		return (0);
	_strcpy(ptr, s1);
	return (ptr);
}

/**
 * _strcmp - compare two string char by char
 * @s1: first string
 * @s2: second string
 * Return: On equal 0 or <0 or >0
 */
int	_strcmp(char *s1, char *s2)
{
	unsigned int i;

	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);
}

/**
  * _strcpy - copies the string pointed to by src
  * @dest: Destination value
  * @src: Source value
  * Return: the pointer to dest
  */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 *_strcat -  concatenates two strings
 *@dest: A pointer to a char
 *@src: A pointer to a char
 *Return: char pointer
 */
char *_strcat(char *dest, char *src)
{
	int i, j;

	i = 0;
	while (dest[i] != '\0')
		i++;

	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	dest[i] = '\0';

	return (dest);
}
