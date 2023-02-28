/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:26:32 by sciftci           #+#    #+#             */
/*   Updated: 2023/02/28 04:57:30 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env(int stdout, char **env)
{
	while (env && *env)
	{
		if (**env)
		{
			ft_putstr_fd(*env++, stdout);
			write(stdout, "\n", 1);
		}
		else
			env++;
	}	
	g_process.code = 0;
}
