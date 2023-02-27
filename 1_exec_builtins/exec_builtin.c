
#include "../minishell.h"

/**
* will try to run a command from is full path
* @param {char *} path to executable
*/

static int	check_exec_cmd(char *cmd, char **argv, char **env)
{
	if (access(cmd, X_OK) == -1 || execve(cmd, argv, env) == -1)
		return (error("minishell", strerror(errno), cmd, errno));
	return (0);
}

/**
* will concatenate a path with a relative path
* @param {char *} path the absolute path
* @param {int} the path string length
* @param {char *} the path relative to path ex: cat
*/
static char	*concat_relative_path(char *path, int n, char *relative)
{
	char	*full;
	char	*start;

	full = malloc(n + ft_strlen(relative) + 2);
	if (full == NULL)
		return (NULL);
	start = full;
	while (n--)
		*full++ = *path++;
	*full++ = '/';
	while (*relative)
		*full++ = *relative++;
	*full = '\0';
	return (start);
}

/**
* will search in PATH folders the command if not a relative or absolute path
*/
int	exec_in_path(char *cmd, char **argv, char **env)
{
	char	**search;
	char	*path;
	char	*file;
	int		len;

	if (*cmd == '.' || *cmd == '/')
		return (check_exec_cmd(cmd, argv, env));
	search = get_envs(env, "PATH");
	if (search == NULL || *search == NULL)
		return (error("minishell", "command not found (PATH is not set)", cmd, 127));
	path = *search;
	while (*path)
	{
		len = 0;
		while (path[len] && path[len] != ':')
			len++;
		file = concat_relative_path(path, len, cmd);
        if (access(file, X_OK) == -1 || execve(file, argv, env) == -1)
            free(file);
        if (!file)
            return (0);
		path += len + (path[len] == ':');
	}
	return (error("minishell", "command not found", cmd, 127));
}

static int	exec_builtin_argv(char **argv, t_env *envs, int stdout)
{
	if (is_env_defined(*argv))
		set(argv, envs);
	else if (!ft_strcmp(*argv, "echo"))
		echo(stdout, argv + 1);
	else if (!ft_strcmp(*argv, "cd"))
		cd(envs, argv + 1);
	else if (!ft_strcmp(*argv, "pwd"))
		pwd(stdout);
	else if (!ft_strcmp(*argv, "export"))
		export(stdout, argv + 1, envs);
	else if (!ft_strcmp(*argv, "unset"))
		unset(argv + 1, envs);
	else if (!ft_strcmp(*argv, "env"))
		env(stdout, envs->exported);
	else if (!ft_strcmp(*argv, "exit"))
		exit_shell(stdout, argv + 1);
	else
		return (-1);
	return(0);
}

int	exec_builtin(char *cmd, t_env *env, int stdout)
{
	char	**argv;

	if (stdout == -1)
		return (1);
	argv = create_argv(cmd, env);
	if (argv == NULL)
		return (0);
	if (exec_builtin_argv(argv, env, stdout) == -1)
		return (free_argv(argv));
	if (stdout != 1)
		close(stdout);
	return (free_argv(argv) || 1);
}
