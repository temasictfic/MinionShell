
#include "minishell.h"

int	tokenize_callback(char **s, int *word_index, int (*token_fn)(), void *arg)
{
	int	word_start_index;

	if (token_fn(*s, *word_index, arg))
		return (-1);
	word_start_index = *word_index;
	while (is_operator((*s)[*word_index]))
		(*word_index)++;
	if (token_fn(*s + word_start_index, *word_index - word_start_index, arg))
		return (-1);
	*s += *word_index;
	while (is_space(**s))
		(*s)++;
	*word_index = 0;
	return (0);
}

int	tokenize(char *s, int (*token)(), void *arg)
{
	int	word_index;
	int	word_start_index;

	word_index = 0;
	while (1)
	{
		if (is_quote(s[word_index]))
		{
			word_start_index = word_index;
			while (s[++word_index] != s[word_start_index])
				if (s[word_index] == '\0')
					return (err("syntax error unclosed token", s, 258));
			word_index++;
		}
		else if (s[word_index] && !is_space(s[word_index]) && !is_operator(s[word_index]))
			while (s[++word_index] && !is_space(s[word_index]) && !is_operator(s[word_index])
				&& !is_quote(s[word_index]))
				;
		if (is_operator(s[word_index]) || is_space(s[word_index]) || s[word_index] == '\0')
			if (tokenize_callback(&s, &word_index, token, arg) == -1)
				return (-1);
		if (s[word_index] == '\0')
			return (0);
	}
}