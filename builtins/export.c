
#include "minishell.h"

static void	print_export(int stdout, char *kv)
{
	putstr(stdout, "declare -x ");
	println(stdout, kv);
}

void	export(int stdout, char **argv, t_env *env)
{
	char	**found;
	char	**exported;

	if (*argv == NULL)
	{
		exported = env->exported;
		while (*exported)
			if (**exported)
				print_export(stdout, *exported++);
		else
			exported++;
	}
	while (*argv)
	{
		if (isenvdefine(*argv))
		{
			env_set(&env->local, *argv);
			env_set(&env->exported, *argv++);
			continue ;
		}
		found = env_get(env->local, *argv++);
		if (found)
			env_set(&env->exported, *found);
	}
	g_process.code = 0;
}
