#include "shell.h"

/**
 * _substr - generate a string of size
 * len starting from the index pos.
 * @s: the given string
 * @start: starting position
 * @len: the size of the string
 * Return: the new generated string
 */
char *_substr(char const *s, unsigned int start, size_t len)
{
	char *substr;
	size_t i;

	i = 0;
	if (!s)
		return (0);
	if (_strlen(s) <= start)
		return (_strdup(""));
	if (len > _strlen(s + start))
		len = _strlen(s + start);
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	while (len > i)
	{
		substr[i] = s[i + start];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

/**
 * create_env - create a list of key and value
 * for the env array
 * @env: array
 * Return: list
 */
t_env *create_env(char **env)
{
	int	i = 0, j;
	t_env *l_env;
	char **splitted;

	l_env = NULL;
	while (env && env[i])
	{
		j = 0;
		splitted = malloc(sizeof(char *) * 3);
		if (!splitted)
			get_error("malloc", 1);

		while (env[i][j] && env[i][j] != '=')
			j++;

		splitted[0] = _substr(env[i], 0, j);
		splitted[1] = _substr(env[i], j + 1, _strlen(env[i]) - j);
		splitted[2] = NULL;

		lstadd_back_env(&l_env, lstnew_env(splitted[0], splitted[1]));
		i++;
		free_array(splitted);
	}
	return (l_env);
}

/**
 * _getenv - get the value of a given key
 * @env: list
 * @name: the key
 * Return: the value or NULL if not found
 */
char *_getenv(t_env *env, char *name)
{
	while (env)
	{
		if (!_strcmp(env->key, name))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/**
 * delete_node - delete a node form the list
 * @head_ref: the head of the list
 * @key: the key refers to the node
 * Return: Nothing
 */
void delete_node(t_env **head_ref, char *key)
{
	t_env	*temp;
	t_env	*prev;

	temp = *head_ref;
	if (temp != NULL && !_strcmp(temp->key, key))
	{
		*head_ref = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
		return;
	}
	while (temp != NULL && _strcmp(temp->key, key))
	{
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL)
		return;
	prev->next = temp->next;
	free(temp->key);
	free(temp->value);
	free(temp);
}

/**
 * cmd_not_found - print an error msg if cmd not found
 * @executable: name of the program
 * @holder: struct of vars
 * Return: Nothing
 */
void cmd_not_found(char *executable, t_shell *holder)
{
	_puts_error(executable);
	_puts_error(": ");
	print_number(holder->cmd_counter);
	_puts_error(": ");
	_puts_error(holder->args[0]);
	_puts_error(": not found\n");
	holder->status = 127;
}
