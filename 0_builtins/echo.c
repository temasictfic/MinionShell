
#include "minishell.h"

void	echo(int stdout, char **args)
{
	int	nl;

	nl = 1;
	while (*args && **args == '-' && ft_is_only_charset(*args + 1, "n") && args++)
		nl = 0;
	while (*args && **args == '\0')
		args++;
	while (*args)
	{
		ft_putstr_fd(*args, stdout);
		if (*++args)
			write(stdout, " ", 1);
	}
	if (nl)
		write(stdout, "\n", 1);
	g_process.code = 0;
}
