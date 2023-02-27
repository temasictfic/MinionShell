
#include "../minishell.h"

void	exit_shell(int stdout, char **argv)
{
	long	v;

	g_process.code = 0;
	write(stdout, "exit\n", 5);
	if (*argv && argv[1])
		return ((void)error("minishell", "exit", "too many arguments", 1));
	if (!*argv)
		exit(0);
	if (!ft_atol(*argv, &v))
	{
		error("minishell: exit", argv[0], "numeric argument required", 1);
		exit(255);
	}
	exit(v);
}
