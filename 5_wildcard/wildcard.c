
#include "minishell.h"

static t_token	**insert(t_token **tokens, int i, char *filename)
{
	int		token_count;
	t_token	**res;

	token_count = -1;
	while (tokens[++token_count])
		;
	res = malloc((token_count + 2) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	res[++token_count] = NULL;
	while (token_count--)
		if (token_count >= i)
			res[token_count + 1] = tokens[token_count];
	    else
		    res[token_count] = tokens[token_count];
	res[i] = malloc(sizeof(t_token) * 2);
	res[i][0].word = ft_strdup(filename);
	res[i][0].expand_char = '\0';
	res[i][1].word = NULL;
	free(tokens);
	return (res);
}

static int	check_pattern(char *pattern, char *file)
{
	while (*file && *pattern)
	{
		if (*pattern == '*' && ++pattern)
		{
			while (*file)
				if (check_pattern(pattern, file++))
					return (1);
		}
		else if (*file++ != *pattern++)
			return (0);
	}
	return (*file == '\0' && *pattern == '\0');
}

static void	wildcard_process(t_token ***tokens, struct dirent *file,
	int *i, int *count)
{
	if ((*count)++)
		*tokens = insert(*tokens, (*i)++, file->d_name);
	else
		(*tokens)[*i]->word = ft_strdup(file->d_name);
}

static void	wildcard_replace(t_token ***tokens, int *i)
{
	DIR				*dir;
	struct dirent	*file;
	int				count;
	char			*pattern;

	dir = opendir(".");
	pattern = (*tokens)[*i]->word;
	if (dir == NULL)
		return ;
	count = 0;
	while (1)
	{
		file = readdir(dir);
		if (file == NULL)
			break ;
		if (!(*pattern == '*' && *file->d_name == '.')
			&& check_pattern(pattern, file->d_name))
			wildcard_process(tokens, file, i, &count);
	}
	if (count)
		free(pattern);
	closedir(dir);
}

void	wildcard_expand(t_token ***tokens)
{
	int	i;

	i = -1;
	while ((*tokens)[++i])
	{
		if ((*tokens)[i][1].word == NULL && (*tokens)[i]->expand_char != '"'
				&& (*tokens)[i]->expand_char != '\'')
			wildcard_replace(tokens, &i);
	}
}