#include "../minishell.h"

int	error(char *name, char *err, char *info, int code)
{
	perror(name);
	perror(": ");
	perror(err);
	perror(": ");
	perror(info);
	perror("\n");
	g_process.code = code;
	return (-1);
}
