
#include "minishell.h"

void	pwd(int stdout)
{
	char	*path;

	path = g_process.pwd;
	if (path != NULL)
		println(stdout, path);
	g_process.code = 0;
}