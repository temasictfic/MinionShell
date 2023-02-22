
#include "minishell.h"

void	echo(int stdout, char **args)
{
	int	nl;

	nl = 1;
	while (*args && **args == '-' && ft_strisonly(*args + 1, "n") && args++)
		nl = 0;
	while (*args && **args == '\0')
		args++;
	while (*args)
	{
		putstr(stdout, *args);
		if (*++args)
			write(stdout, " ", 1);
	}
	if (nl)
		write(stdout, "\n", 1);
	g_process.code = 0;
}