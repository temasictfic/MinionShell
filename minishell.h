#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>

#define PATH_BUF 4096

#define START "\033[0;36m"
#define BOLD "\033[1m"
#define END "\033[0m"

typedef struct s_token
{
	char *word;
	char expand_char;
} t_token;

typedef struct s_arg
{
	t_env *env;
	char **subcmds;
	int stdin;
} t_arg;

typedef struct s_process
{
	int pid;
	int code;
	char *pwd;
} t_process;

extern t_process g_process;

typedef struct s_env
{
	char **local;
	char **exported;
} t_env;

typedef struct s_redirection
{
	char *value;
	int type;
	int expanded;
	int fd;
} t_redirection;

typedef enum e_redir_type
{
	REDIR_NOT = 0,
	REDIR_INPUT = 1,
	REDIR_OUTPUT = 2,
	REDIR_HEREDOC = 4,
	REDIR_APPEND = 8
} t_redir_type;

/* builtins/ */
	/* env */
void	env_expand(char **envs, t_token **tokens);
int	is_env_defined(char *s);
char	**get_envs(char **envs, char *keyvalue);
void	set_env(char ***envs, char *keyvalue);
void	env_init(t_env *env, char **keyvalue_arr);
void	env(int stdout, char **env);

void	cd(t_env *env, char **argv);
void	echo(int stdout, char **args);
void	exit_shell(int stdout, char **argv);
void	export(int stdout, char **argv, t_env *env);
void	pwd(int stdout);
void	set(char **argv, t_env *env);
void	unset(char **argv, t_env *env);

/* exec_builtins */
int	exec_in_path(char *cmd, char **argv, char **env);
int	exec_builtin(char *cmd, t_env *env, int stdout);

/* parse */
t_token	**create_tokens(char *s);
char	**create_argv(char *cmd, t_env *env);
int	exec_tokens(char *cmd, t_env *env);
int	tokenize(char *s, int (*token)(), void *arg);

/* pipes */
char	*or_and(t_env *env, char *s, int exec, int brace);
char	**pipe_split(char *s);
void	pipe_parse(t_env *env, char *cmd);
int	exec_heredocs(t_redirection *redirs, char **buffer);

/* redirects */
int	file_flags(int type);
void	redirect_in(int stdin, t_redirection *redirs, char *s);
int	redirect_out(t_redirection *redirs);
void	close_out(t_redirection *redirs);
t_redirection	*exec_redirections(char *cmd, t_env *env);

/* wildcard */
void	wildcard_expand(t_token ***tokens);

/* utils */
int	error(char *name, char *err, char *info, int code);
int	free_argv(char **argv);
int	free_redirections(t_redirection *redir);
int	free_tokens(t_token **tokens);
int	is_env_char(char c);
int	is_only_charset(const char *s, char *charset);
int	is_operator(char c);
int	is_quote(char c);
int	is_redir(char *s, int redir_count);
int	is_space(char c);

#endif