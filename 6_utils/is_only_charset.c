/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_only_charset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:28:36 by sciftci           #+#    #+#             */
/*   Updated: 2023/02/28 04:28:37 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_only_charset(const char *s, char *charset)
{
	while (*s)
		if (ft_strchr(charset, *s++) == NULL)
			return (0);
	return (1);
}
