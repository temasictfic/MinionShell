
#include "../../minishell.h"

void	env(int stdout, char **env)
{
	while (env && *env)
		if (**env)
		{
			ft_putstr_fd(*env++, stdout);
			write(stdout, "\n", 1);
		}
		else
			env++;
	g_process.code = 0;
}
