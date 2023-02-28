/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:27:03 by sciftci           #+#    #+#             */
/*   Updated: 2023/02/28 04:57:55 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	print_export(int stdout, char *keyvalue)
{
	ft_putstr_fd("declare -x ", stdout);
	ft_putstr_fd(keyvalue, stdout);
	write(stdout, "\n", 1);
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
		if (is_env_defined(*argv))
		{
			set_env(&env->local, *argv);
			set_env(&env->exported, *argv++);
			continue ;
		}
		found = get_envs(env->local, *argv++);
		if (found)
			set_env(&env->exported, *found);
	}
	g_process.code = 0;
}
