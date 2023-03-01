/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_get_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:26:25 by sciftci           #+#    #+#             */
/*   Updated: 2023/02/28 04:54:19 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_env_defined(char *s)
{
	if (ft_isdigit(*s) || !is_env_char(*s++))
		return (0);
	while (is_env_char(*s))
		s++;
	if (*s == '=')
		return (1);
	return (0);
}

char	**get_envs(char **envs, char *keyvalue)
{
	char	*env_str;
	int		i;

	if (envs == NULL)
		return (NULL);
	while (*envs)
	{
		env_str = *envs;
		i = 0;
		while (*env_str)
			if (!is_env_char(keyvalue[i]) && !is_env_char(*env_str))
				return (envs);
		else if (*env_str++ != keyvalue[i++])
			break ;
		envs++;
	}
	return (NULL);
}

void	set_env(char ***envs, char *keyvalue)
{
	int		len;
	char	**new_envs;

	new_envs = get_envs(*envs, keyvalue);
	if (new_envs)
	{
		free(*new_envs);
		*new_envs = ft_strdup(keyvalue);
		return ;
	}
	len = 1;
	if (*envs)
		while ((*envs)[len - 1])
			len++;
	new_envs = malloc((len + 1) * sizeof(char *));
	new_envs[len] = NULL;
	new_envs[--len] = ft_strdup(keyvalue);
	while (len--)
		new_envs[len] = (*envs)[len];
	if (*envs)
		free(*envs);
	*envs = new_envs;
}

void	env_init(t_env *env, char **keyvalue_arr)
{
	while (*keyvalue_arr)
	{
		set_env(&(env->exported), *keyvalue_arr);
		set_env(&(env->local), *keyvalue_arr++);
	}
}
