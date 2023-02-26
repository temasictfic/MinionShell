#include "minishell.h"

void	set(char **argv, t_env *env)
{
	while (*argv)
	{
		set_env(&env->local, *argv);
		if (get_envs(env->exported, *argv))
			get_envs(&env->exported, *argv);
		argv++;
	}
	g_process.code = 0;
}
