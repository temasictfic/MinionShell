
#include "../../minishell.h"

static char	*env_join(char *s, char *value, int *i, int len)
{
	char	*out;
	int		value_len;

	if (value == NULL)
		return (s);
	value_len = ft_strlen(++value);
	out = malloc(sizeof(char) * (ft_strlen(s) + value_len - len + 1));
	ft_strlcpy(out, s, *i);
	ft_strcat(out, value);
	ft_strcat(out, s + *i + len);
	*i += len + 1;
	free(s);
	return (out);
}

static char	*env_var(char **envs, char *s, int *i)
{
	int		len;
	char	**keyvalue_arr;

	if (s[*i] == '?')
		return (env_join(s, ft_itoa(g_process.code) - 1, i, 1));
	len = 0;
	while (is_env_char(s[*i + len]))
		len++;
	keyvalue_arr = get_envs(envs, s + *i);
	if (keyvalue_arr == NULL)
		return (s);
	return (env_join(s, ft_strchr(*keyvalue_arr, '='), i, len));
}

static char	*env_replace(char **envs, char *s)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '$')
		{
			if (s[++i] == '\0' || s[i] == ' ')
				continue ;
			s = env_var(envs, s, &i);
		}
	}
	return (s);
}

void	env_expand(char **envs, t_token **tokens)
{
	int	i;

	while (*tokens)
	{
		i = -1;
		while ((*tokens)[++i].word)
			if ((*tokens)[i].expand_char != '\''
					&& (*tokens)[i].expand_char != '"'
					&& *(*tokens)[i].word == '$'
					&& (*tokens)[i].word[1] == '\0'
					&& (*tokens)[i + 1].word
					&& ((*tokens)[i + 1].expand_char == '\''
						|| (*tokens)[i + 1].expand_char == '"'))
				*(*tokens)[i].word = '\0';
		else if ((*tokens)[i].expand_char != '\'')
			(*tokens)[i].word = env_replace(envs, (*tokens)[i].word);
		tokens++;
	}
}
