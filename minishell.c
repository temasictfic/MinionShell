#include "minishell.h"

t_process	g_process = {0, 0, NULL};

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
			error("minishell", "pathname length exceeds the PATH_BUF size", strerror(errno), 1);
		return ;
	}
	tmp = ft_strjoin("PWD=", path);
	set_env(&env->local, tmp);
	set_env(&env->exported, tmp);
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
	set_env_at_start(&env);
	while (1)
	{
		g_process.pid = 0;
		line = readline(START BOLD "minishell🐚 " END);
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		if (!is_only_charset(line, "\t\n\v\f\r "))
			or_and(&env, line, 1, 0);
		free(line);
	}
	printf("exit\n");
	return (0);
}
