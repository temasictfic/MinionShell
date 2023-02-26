#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>

# define PATH_BUF	4096

# define START "\033[0;36m"
# define BOLD "\033[1m"
# define END "\033[0m"

extern t_process	g_process;

typedef struct s_token
{
	char	*word;
	char	expand_char;
}	t_token;

typedef struct s_arg
{
	t_env	*env;
	char	**subcmds;
	int		stdin;
}	t_arg;


typedef struct s_process
{
	int		pid;
	int		code;
	char	*pwd;
}	t_process;

typedef struct s_env
{
	char	**local;
	char	**exported;
}	t_env;

typedef struct s_redirection
{
	char	*value;
	int		type;
	int		expanded;
	int		fd;
}	t_redirection;

typedef enum e_redir_type
{
    REDIR_NOT = 0,
    REDIR_INPUT = 1,
    REDIR_OUTPUT = 2,
    REDIR_HEREDOC = 4,
    REDIR_APPEND = 8
} t_redir_type;

#endif