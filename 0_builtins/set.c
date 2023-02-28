/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:27:13 by sciftci           #+#    #+#             */
/*   Updated: 2023/02/28 04:27:14 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set(char **argv, t_env *env)
{
	while (*argv)
	{
		set_env(&env->local, *argv);
		if (get_envs(env->exported, *argv))
			get_envs(env->exported, *argv);
		argv++;
	}
	g_process.code = 0;
}
