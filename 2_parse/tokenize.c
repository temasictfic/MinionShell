/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:27:46 by sciftci           #+#    #+#             */
/*   Updated: 2023/02/28 04:45:31 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	tokenize_callback(char **s, int *idx, int (*token_fn)(), void *arg)
{
	int	start_idx;

	if (token_fn(*s, *idx, arg))
		return (-1);
	start_idx = *idx;
	while (is_operator((*s)[*idx]))
		(*idx)++;
	if (token_fn(*s + start_idx, *idx - start_idx, arg))
		return (-1);
	*s += *idx;
	while (is_space(**s))
		(*s)++;
	*idx = 0;
	return (0);
}

int	tokenize(char *s, int (*token)(), void *arg)
{
	int	idx;
	int	start_idx;

	idx = 0;
	while (1)
	{
		if (is_quote(s[idx]))
		{
			start_idx = idx;
			while (s[++idx] != s[start_idx])
				if (s[idx] == '\0')
					return (error(SH, "syntax error unclosed token", s, 258));
			idx++;
		}
		else if (s[idx] && !is_space(s[idx]) && !is_operator(s[idx]))
			while (s[++idx] && !is_space(s[idx]) && !is_operator(s[idx])
				&& !is_quote(s[idx]))
				;
		if (is_operator(s[idx]) || is_space(s[idx]) || s[idx] == '\0')
			if (tokenize_callback(&s, &idx, token, arg) == -1)
				return (-1);
		if (s[idx] == '\0')
			return (0);
	}
}
