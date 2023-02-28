/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:26:40 by sciftci           #+#    #+#             */
/*   Updated: 2023/02/28 04:26:44 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(t_env *env, char **argv)
{
	char	*pwd;
	char	buf[PATH_BUF];
	char	*status;

	if (*argv)
		status = *argv;
	else
		status = getenv("HOME");
	if (chdir(status) == -1)
		error("cd", strerror(errno), status, errno);
	else
	{
		pwd = ft_strjoin("OLDPWD=", g_process.pwd);
		set_env(&env->local, pwd);
		set_env(&env->exported, pwd);
		free(pwd);
		pwd = ft_strjoin("PWD=", getcwd(buf, PATH_BUF));
		set_env(&env->local, pwd);
		set_env(&env->exported, pwd);
		free(pwd);
		free(g_process.pwd);
		g_process.pwd = ft_strdup(getcwd(buf, PATH_BUF));
		g_process.code = 0;
	}
}
