
#include "minishell.h"

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
	keyvalue_arr = env_get(envs, s + *i);
	if (keyvalue_arr == NULL)
		return (s);
	return (env_join(s, ft_strchr(*keyvalue_arr, '='), i, len));
}

char	*env_replace(char **envs, char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == '$' && !(s[i+1] == '\0' || s[i+1] == ' '))
			s = env_var(envs, s, &++i);
	return (s);
}

void	env_expand(char **envs, t_token **tokens)
{
	int	i;

	while (*tokens)
	{
		i = -1;
		while ((*tokens)[++i].value)
			if ((*tokens)[i].expandable != '\''
					&& (*tokens)[i].expandable != '"'
					&& *(*tokens)[i].value == '$'
					&& (*tokens)[i].value[1] == '\0'
					&& (*tokens)[i + 1].value
					&& ((*tokens)[i + 1].expandable == '\''
						|| (*tokens)[i + 1].expandable == '"'))
				*(*tokens)[i].value = '\0';
		else if ((*tokens)[i].expandable != '\'')
			(*tokens)[i].value = env_replace(envs, (*tokens)[i].value);
		tokens++;
	}
}
