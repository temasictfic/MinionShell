#include "../minishell.h"

static int	get_fd(t_redirection *redirs, char *subcmds, int fd)
{
	if (subcmds == NULL)
		fd = 1;
	while ((++redirs)->value)
	{
		if (*redirs->value && redirs->type == REDIR_INPUT
			&& access(redirs->value + 1, R_OK))
			return (error("minishell", redirs->value + 1, strerror(errno), 1));
		else if (*redirs->value && (redirs->type == REDIR_OUTPUT
				|| redirs->type == REDIR_APPEND))
		{
			if (fd != 1)
				close(fd);
			fd = open(redirs->value + 1, file_flags(redirs->type),
					S_IRWXU);
			if (fd == -1)
				return (error("minishell", redirs->value + 1, "permission denied", 1));
		}
	}
	return (fd);
}

static void	pipe_wait(pid_t pid, char *s,
		t_redirection *redirs)
{
	if (pid)
	{
		g_process.pid = pid;
		waitpid(pid, &g_process.code, 0);
		g_process.code = WEXITSTATUS(g_process.code);
	}
	if (s)
		free(s);
	free_redirections(redirs);
}

static int	pipe_not_builtin(t_arg arg, t_redirection *redirs, int *fd, char *s)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		redirect_in(arg.stdin, redirs, s);
		if (arg.subcmds[1])
			dup2(fd[1], 1);
		close(fd[0]);
		if (redirect_out(redirs + 1) || exec_tokens(redirs->value, arg.env))
		{
			close_out(redirs + 1);
			exit(127);
		}
		close_out(redirs + 1);
		exit(0);
	}
	return (pid);
}

static void	pipe_execute(t_env *env, char **subcmds, int stdin)
{
	t_redirection	*redirs;
	int				fd[2];
	pid_t			pid;
	char			*s;

	redirs = exec_redirections(*subcmds, env);
	if (redirs == NULL)
		return ;
	if (exec_heredocs(redirs + 1, &s))
		return ((void)free_redirections(redirs));
	pipe(fd);
	pid = 0;
	if (!exec_builtin(redirs->value, env, get_fd(redirs, subcmds[1], fd[1])))
		pid = pipe_not_builtin((t_arg){env, subcmds, stdin}, redirs, fd, s);
	close(fd[1]);
	if (subcmds[1])
		pipe_execute(env, subcmds + 1, fd[0]);
	close(fd[0]);
	pipe_wait(pid, s, redirs);
}

void	pipe_parse(t_env *env, char *cmd)
{
	char	**subcmds;
	int		i;

	subcmds = pipe_split(cmd);
	if (subcmds == NULL)
    {
        free(cmd);
        return;
    }
	i = 0;
	while (subcmds[i] && subcmds[i + 1])
	{
		if (*subcmds[++i] == '\0')
		{
			free_argv(subcmds);
			free(cmd);
			error("minishell", "syntax error near unexpected token", "|", 258);
            return;
		}
	}
	if (*subcmds && **subcmds)
		pipe_execute(env, subcmds, 0);
	free_argv(subcmds);
	free(cmd);
}
