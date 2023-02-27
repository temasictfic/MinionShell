
#include "../minishell.h"

static char	*token_join(t_token *token)
{
	int		total_len;
	char	*joined_str;
	int		i;
	int		j;

	total_len = 0;
	i = -1;
	while (token[++i].word)
	{
		j = -1;
		while (token[i].word[++j])
			total_len++;
	}
	joined_str= malloc((total_len + 1) * sizeof(char));
	joined_str[total_len] = '\0';
	total_len = 0;
	i = -1;
	while (token[++i].word)
	{
		j = -1;
		while (token[i].word[++j])
			joined_str[total_len++] = token[i].word[j];
	}
	return (joined_str);
}

static char	**token_to_argv(t_token **tokens)
{
	char	**argv;
	int		token_count;

	token_count = 0;
	while (tokens[token_count++])
		;
	argv = malloc(token_count * sizeof(char *));
	if (argv == NULL)
		return (NULL);
	argv[--token_count] = NULL;
	while (token_count--)
		argv[token_count] = token_join(tokens[token_count]);
	return (argv);
}

char	**create_argv(char *cmd, t_env *env)
{
	char	**argv;
	t_token	**tokens;

	tokens = create_tokens(cmd);
	if (tokens == NULL || *tokens == NULL)
	{
		free_tokens(tokens);
		return (NULL);
	}
	env_expand(env->local, tokens);
	wildcard_expand(&tokens);
	if (tokens[0]->word == NULL)
	{
		free_tokens(tokens);
		return (NULL);
	}
	argv = token_to_argv(tokens);
	free_tokens(tokens);
	return (argv);
}

int	exec_tokens(char *cmd, t_env *env)
{
	char	**argv;

	argv = create_argv(cmd, env);
	if (argv == NULL)
		return (1);
	exec_in_path(argv[0], argv, env->exported);
	free_argv(argv);
	return (1);
}
