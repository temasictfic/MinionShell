/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:29:36 by sciftci           #+#    #+#             */
/*   Updated: 2023/02/28 04:29:37 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, int n)
{
	char	*out;

	out = malloc((n + 1) * sizeof(char));
	out[n] = '\0';
	while (n--)
		out[n] = s[n];
	return (out);
}
