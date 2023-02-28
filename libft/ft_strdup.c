/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:29:24 by sciftci           #+#    #+#             */
/*   Updated: 2023/02/28 04:29:25 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *str)
{
	char	*s;
	int		len;

	len = ft_strlen(str) + 1;
	s = malloc(len * sizeof(char));
	ft_strlcpy(s, str, len);
	return (s);
}
