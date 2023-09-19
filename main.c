#include "shell.h"

/**
 * valid_cmd - get the full path of the command
 * if exist
 * @cmd: command name
 * @env: env
 * Return: the full path of command or NULL
 */
char *valid_cmd(char *cmd, t_env *env)
{
	char *tmp;
	char *res;
	char *buffer;
	char *path = _getenv(env, "PATH");

	if (_strchr(cmd, '/') && !access(cmd, F_OK))
		return (_strdup(cmd));
	if (!path || !*path)
		return (NULL);

	tmp = _strdup(path);
	if (!tmp)
		get_error("_strdup", 1);
	res = strtok(tmp, ":");
	while (res)
	{
		buffer = malloc(_strlen(res) + _strlen(cmd) + 2);
		_strcpy(buffer, res);
		_strcat(buffer, "/");
		_strcat(buffer, cmd);
		if (!access(buffer, F_OK))
		{
			free(tmp);
			return (buffer);
		}
		free(buffer);
		res = strtok(NULL, ":");
	}
	free(tmp);
	return (NULL);
}

/**
 * prompt - print the prompt and get the command ready
 * @my_env: env list
 * @status: status
 * Return: the input command and it's param
 */
char **prompt(t_env **my_env, int status)
{
	char **args;
	char *buffer = NULL;
	size_t buff_size = 0;
	ssize_t read;

	if (isatty(STDIN_FILENO))
		write(1, "( ^_^)/>", 8);

	read = getline(&buffer, &buff_size, stdin);
	if (read == -1)
	{
		free(buffer);
		lstclear_env(my_env);
		exit(status);
	}

	args = _split(buffer, " \t\n");
	free(buffer);
	if (!*args)
	{
		free_array(args);
		return (NULL);
	}
	return (args);
}

/**
 * run - execute the command
 * @executable: name of the program
 * @holder: struct
 * @env: env
 * Return: Nothing
 */
void run(char *executable, t_shell *holder, char **env)
{
	int pid;

	if (!is_built_in(holder->args[0]))
	{
		pid = fork();
		if (pid == -1)
			get_error("fork", 1);
		if (pid == 0)
		{
			if (execve(holder->vcmd, holder->args, env) == -1)
				get_error(executable, 1);
		}
		else
		{
			if (waitpid(pid, &holder->status, 0) == -1)
				get_error("waitpid", 1);
		}
	}
	else
	{
		if (!_strcmp(holder->args[0], "exit"))
		{
			free(holder->vcmd);
			free_array(holder->args);
			lstclear_env(&holder->my_env);
			exit(holder->status);
		}
		else if (!_strcmp(holder->args[0], "env"))
			_env(holder->my_env);
	}
}

/**
 * main - entry point
 * @argc: number of args
 * @argv: args
 * @env: env
 * Return: int
 */
int main(int argc, char **argv, char **env)
{
	t_shell holder;

	(void) argc;

	holder.status = 0;
	holder.cmd_counter = 0;
	holder.my_env = create_env(env);
	while (1)
	{
		(holder.cmd_counter)++;
		holder.args = prompt(&holder.my_env, holder.status);
		if (!holder.args)
			continue;
		holder.vcmd = valid_cmd(holder.args[0], holder.my_env);
		if (!is_built_in(holder.args[0]) && !holder.vcmd)
		{
			cmd_not_found(argv[0], &holder);
			free_array(holder.args);
			continue;
		}
		run(argv[0], &holder, env);
		free_array(holder.args);
		free(holder.vcmd);
	}

}
