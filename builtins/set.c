#include "minishell.h"

void	set(char **argv, t_env *env)
{
	while (*argv)
	{
		env_set(&env->local, *argv);
		if (env_get(env->exported, *argv))
			env_set(&env->exported, *argv);
		argv++;
	}
	g_process.code = 0;
}
