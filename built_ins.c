#include "shell.h"

/**
 * _env - prinrt the environment variable
 * @env: the first node of linked list
 * Return: Nothing
 */
void _env(t_env *env)
{
	while (env)
	{
		_puts(env->key);
		_puts("=");
		_puts(env->value);
		write(1, "\n", 1);
		env = env->next;
	}
}
