/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:27:08 by sciftci           #+#    #+#             */
/*   Updated: 2023/02/28 04:27:11 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(int stdout)
{
	char	*path;

	path = g_process.pwd;
	if (path != NULL)
	{
		ft_putstr_fd(path, stdout);
		write(stdout, "\n", 1);
	}
	g_process.code = 0;
}
