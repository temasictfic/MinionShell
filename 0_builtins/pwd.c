
#include "../minishell.h"

void	pwd(int stdout)
{
	char	*path;

	path = g_process.pwd;
	if (path != NULL)
	{
		ft_putstr_fd(path, stdout);
		write(stdout, "\n", 1);
	}
	g_process.code = 0;
}
