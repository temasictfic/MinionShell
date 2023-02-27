
#include "../minishell.h"

static int	incr_pipe_count(char *s, int word_len, int *pipe_count)
{
	if (word_len == 1 && *s == '|')
		(*pipe_count)++;
	return (0);
}

static int	check_pipe_error(char **pipes_ptr, int word_len)
{
	if (word_len != 1 || **pipes_ptr == '\0')
		return (error("minishell", "syntax error near unexpected token", "|", 258));
	*++pipes_ptr = ft_strdup("");
	*++pipes_ptr = NULL;
	return (0);
}

static int	fill_pipes(char *s, int word_len, char **pipes_ptr)
{
	char	*tmp;
	int		i;

	if (word_len <= 0)
		return (0);
	while (pipes_ptr[0] && pipes_ptr[1])
		pipes_ptr++;
	if (*s == '|')
		return (check_pipe_error(pipes_ptr, word_len));
	tmp = malloc((word_len + ft_strlen(*pipes_ptr) + 2) * sizeof(char));
	i = -1;
	while ((*pipes_ptr)[++i])
		tmp[i] = (*pipes_ptr)[i];
	tmp[i] = ' ';
	while (word_len--)
		tmp[++i] = *s++;
	tmp[++i] = '\0';
	free(*pipes_ptr);
	*pipes_ptr = tmp;
	return (0);
}

char	**pipe_split(char *s)
{
	int		pipe_count;
	char	**pipes_ptr;

	pipe_count = 2;
	if (tokenize(s, incr_pipe_count, &pipe_count) == -1)
		return (NULL);
	pipes_ptr = malloc(pipe_count * sizeof(char *));
	if (pipes_ptr == NULL)
		return (NULL);
	pipes_ptr[0] = ft_strdup("");
	pipes_ptr[1] = NULL;
	if (tokenize(s, (int (*)()) fill_pipes, pipes_ptr) == -1)
	{
		free_argv(pipes_ptr);
		return (NULL);
	}
	return (pipes_ptr);
}
