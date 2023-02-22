
#include "minishell.h"

void	unset(char **argv, t_env *env)
{
	char	**found;

	while (*argv)
	{
		found = env_get(env->local, *argv);
		if (found)
			**found = '\0';
		found = env_get(env->exported, *argv++);
		if (found)
			**found = '\0';
	}
	g_process.code = 0;
}