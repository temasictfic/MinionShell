#include "minishell.h"

t_process	g_process = {0, 0, NULL};

int	error(char *name, char *err, char *info, int code)
{
	perror(name);
	perror(": ");
	perror(err);
	perror(": ");
	perror(info);
	perror("\n");
	g_process.code = code;
	return (-1);
}

static void	handle_sigquit(int signum)
{
	(void)signum;
	if (g_process.pid)
	{
		if (kill(g_process.pid, SIGQUIT) == 0)
			printf("Quit: 3\n");
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
	g_process.pid = 0;
}

static void	handle_sigint(int signum)
{
	(void)signum;
	printf("\n");
	if (g_process.pid)
		kill(g_process.pid, SIGINT);
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_process.pid = 0;
}

static void	set_env_at_start(t_env *env)
{
	char	path[PATH_BUF];
	char	*tmp;

	if (getcwd(path, PATH_BUF) == NULL)
	{
		if (errno == ERANGE)
			err("minishell", "pathname length exceeds the buffer size", 1);
		return ;
	}
	tmp = ft_strjoin("PWD=", path);
	env_set(&env->local, tmp);
	env_set(&env->exported, tmp);
	g_process.pwd = ft_strdup(path);
	free(tmp);
}

int	main(int argc, char **argv, char **envs)
{
	char			*line;
	static t_env	env = {NULL, NULL};

	(void)argc;
	(void)argv;
	env_init(&env, envs);
	signal(SIGQUIT, handle_sigquit);
	signal(SIGINT, handle_sigint);
	set_env_at_start(&envs);
	while (1)
	{
		g_process.pid = 0;
		line = readline(START BOLD "minishell🐚 " END);
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		if (!is_only_charset(line, "\t\n\v\f\r "))
			orand(&env, line, 1, 0);
		free(line);
	}
	printf("exit\n");
	return (0);
}
