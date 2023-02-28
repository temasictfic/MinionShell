/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:27:51 by sciftci           #+#    #+#             */
/*   Updated: 2023/02/28 04:40:43 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*or_and_exec(t_env *env, char *s, int exec)
{
	int	n;
	int	m;

	if (*s == '(')
		return (or_and(env, s + 1, exec, 1));
	else
	{
		n = -1;
		while (s[++n] && s[n] != '(' && s[n] != ')' && !(s[n] == '&' && s[n
					+ 1] == '&') && !(s[n] == '|' && s[n + 1] == '|'))
		{
			if (s[n] == '"' || s[n] == '\'')
			{
				m = n;
				while (s[++n] && s[n] != s[m])
					;
			}
		}
		if (n && exec)
			pipe_parse(env, ft_substr(s, n));
		else if (n == 0 && error(SH, "syntax error expected token", s, 258))
			return (NULL);
		return (s + n);
	}
}

char	*or_and(t_env *env, char *s, int exec, int brace)
{
	while (*s && *s != ')')
	{
		while (is_space(*s))
			s++;
		s = or_and_exec(env, s, exec);
		if (s == NULL)
			return (NULL);
		while (is_space(*s))
			s++;
		if ((*s == '&' && s[1] == '&') || (*s == '|' && s[1] == '|'))
		{
			if (((*s == '&' && g_process.code) || (*s == '|'
						&& !g_process.code)))
				exec = 0;
			s += 2;
		}
		else if (*s != '\0' && *s != ')' && error(SH,
				"syntax error expected token", s, 258))
			return (NULL);
	}
	if ((!brace && *s == ')' && error(SH, "syntax error near unexpected token",
				")", 258)) || (brace && *s != ')' && error(SH,
				"syntax error expected token", ")", 258)))
		return (NULL);
	return (s + brace);
}
