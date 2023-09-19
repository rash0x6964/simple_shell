#include "shell.h"

/**
 * lstnew_env - create new t_env node
 * @key: key
 * @value: value
 * Return: new node or NULL
 */
t_env *lstnew_env(char *key, char *value)
{
	t_env *node;

	if (!value)
		value = "";
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->key = _strdup(key);
	node->value = _strdup(value);
	node->next = NULL;
	return (node);
}

/**
 * lstlast_env - give u the laste node of the list
 * @lst: list
 * Return: the last node or NULL
 */
t_env *lstlast_env(t_env *lst)
{
	if (lst)
	{
		while (lst && lst->next)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

/**
 * lstclear_env - free all the node in the list
 * @lst: list
 * Return: Nothing
 */
void lstclear_env(t_env **lst)
{
	t_env *node;

	if (!lst)
		return;
	while (*lst)
	{
		node = *lst;
		*lst = (*lst)->next;
		free(node->key);
		free(node->value);
		free(node);
	}
	*lst = NULL;
}

/**
 * lstadd_back_env - add node the the back of the list
 * @lst: the head of the list
 * @new: the node u wanna add
 * Return: Nothing
 */
void lstadd_back_env(t_env **lst, t_env *new)
{
	t_env *temp;

	if (!new)
		return;
	if (*lst)
	{
		temp = lstlast_env(*lst);
		temp->next = new;
			return;
	}
	*lst = new;
}
