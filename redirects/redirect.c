

#include "minishell.h"

static int	is_redir(char *s, int redir_count)
{
	if (redir_count == 1 && (s[0] == '<' || s[0] == '>'))
		return (1);
	if (redir_count == 2 && ((*s == '<' && s[1] == '<') || (*s == '>' && s[1] == '>')))
		return (1);
	return (0);
}

static void	incr_redir_count(char *s, int word_len, int *redir_count)
{
	if (is_redir(s, word_len))
		(*redir_count)++;
}

static int	assign_redir_type(char *s, int word_len, t_redirection *redir_ptr)
{
	if (s[word_len] == '\0')
		return (error("minishell", "syntax error near unexpected token", s, 258));
	redir_ptr[1].value = ft_strdup("");
	if (word_len == 2 && s[1] == '<')
		redir_ptr[1].type = REDIR_HEREDOC;
	else if (word_len == 2 && s[1] == '>')
		redir_ptr[1].type = REDIR_APPEND;
	else if (word_len == 1 && *s == '<')
		redir_ptr[1].type = REDIR_INPUT;
	else
		redir_ptr[1].type = REDIR_OUTPUT;
	redir_ptr[1].expanded = 0;
	redir_ptr[2].value = NULL;
	return (0);
}

static int	fill_redirects(char *s, int word_len, t_redirection *redir_ptr)
{
	char			*tmp;
	t_redirection	*start;
	int				i;

	if (word_len <= 0)
		return (0);
	start = redir_ptr;
	while (redir_ptr->value && redir_ptr[1].value)
		redir_ptr++;
	if (is_redir(s, word_len))
		return (assign_redir_type(s, word_len, redir_ptr));
	if (redir_ptr->expanded)
		redir_ptr = start;
	tmp = malloc((word_len + ft_strlen(redir_ptr->value) + 2) * sizeof(char));
	i = -1;
	while (redir_ptr->value[++i])
		tmp[i] = redir_ptr->value[i];
	tmp[i] = ' ';
	while (word_len--)
		tmp[++i] = *s++;
	tmp[++i] = '\0';
	free(redir_ptr->value);
	redir_ptr->value = tmp;
	redir_ptr->expanded = 1;
	return (0);
}

t_redirection	*exec_redirections(char *cmd, t_env *env)
{
	t_redirection	*redir_ptr;
	int				redir_count;

	(void) env;
	redir_count = 2;
	if (tokenize(cmd, incr_redir_count, &redir_count) == -1)
		return (NULL);
	redir_ptr = malloc(redir_count * sizeof(t_redirection));
	if (redir_ptr == NULL)
		return (NULL);
	redir_ptr[0].value = ft_strdup("");
	redir_ptr[0].type = REDIR_NOT;
	redir_ptr[1].value = NULL;
	if (tokenize(cmd, (int (*)()) fill_redirects, redir_ptr))
	{
		free_redirections(redir_ptr);
		return (NULL);
	}
	return (redir_ptr);
}
