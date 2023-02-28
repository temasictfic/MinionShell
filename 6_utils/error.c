/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:28:26 by sciftci           #+#    #+#             */
/*   Updated: 2023/02/28 11:55:58 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error(char *name, char *err, char *info, int code)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(info, 2);
	ft_putstr_fd("\n", 2);
	g_process.code = code;
	return (-1);
}
