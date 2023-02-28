/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:26:56 by sciftci           #+#    #+#             */
/*   Updated: 2023/02/28 04:37:24 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_shell(int stdout, char **argv)
{
	long	v;

	g_process.code = 0;
	write(stdout, "exit\n", 5);
	if (*argv && argv[1])
		return ((void)error(SH, "exit", "too many arguments", 1));
	if (!*argv)
		exit(0);
	if (!ft_atol(*argv, &v))
	{
		error("minishell: exit", argv[0], "numeric argument required", 1);
		exit(255);
	}
	exit(v);
}
