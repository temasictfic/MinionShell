/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:28:26 by sciftci           #+#    #+#             */
/*   Updated: 2023/02/28 04:28:27 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	error(char *name, char *err, char *info, int code)
{
	perror(name);
	perror(": ");
	perror(err);
	perror(": ");
	perror(info);
	perror("\n");
	g_process.code = code;
	return (-1);
}
