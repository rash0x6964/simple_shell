#ifndef SHELL_H
# define SHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
#include <sys/wait.h>

/**
 *struct s_env - New data type as dog
 *@key: key
 *@value: value
 *@next: next node
 */
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/**
 *struct s_shell - New data type as dog
 *@status: status code
 *@vcmd: valid command
 *@args: args u enter
 *@cmd_counter: the cmd number
 *@my_env: env
 */
typedef struct s_shell
{
	int status;
	char *vcmd;
	char **args;
	size_t cmd_counter;
	struct s_env *my_env;
}	t_shell;


char *_strdup(char *s1);
int _strcmp(char *s1, char *s2);
char *_strchr(char *str, char c);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);

void _puts_error(char *str);
void _puts(char *str);
void print_number(int n);
char **_split(char *str, char *delim);

size_t _strlen(const char *s);
int is_built_in(char *cmd);
void get_error(char *str, int status);
void free_array(char **array);
int	args_counter(char *str, char *charsets);

t_env *lstnew_env(char *key, char *value);
t_env *lstlast_env(t_env *lst);
void lstclear_env(t_env **lst);
void lstadd_back_env(t_env **lst, t_env *new);

t_env *create_env(char **env);
char *_getenv(t_env *env, char *name);
void delete_node(t_env **head_ref, char *key);
void cmd_not_found(char *executable, t_shell *holder);



void _env(t_env *env);

#endif
