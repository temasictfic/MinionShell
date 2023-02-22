
#include "minishell.h"

void	env(int stdout, char **env)
{
	while (env && *env)
		if (**env)
			println(stdout, *env++);
		else
			env++;
	g_process.code = 0;
}