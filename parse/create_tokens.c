
#include "minishell.h"

static void	incr_token_count(char *s, int word_len, int *token_count)
{
	(void)s;
	if (word_len > 0)
		(*token_count)++;
}

static void	tokenize_word(char *s, int word_index, void (*itc_or_cqw)(char *s, int n, void *arg),
		void *token_count_or_ptr)
{
	int	word_len;

	while (word_index > 0)
	{
		if (is_quote(*s))
		{
			word_len = 0;
			while (word_index-- > 0 && s[++word_len] != *s)
				;
			itc_or_cqw(s, word_len, token_count_or_ptr);
			s += word_len + 1;
			word_index--;
		}
		else
		{
			word_len = 0;
			while (word_index-- > 0 && !is_quote(s[word_len]))
				word_len++;
			itc_or_cqw(s, word_len, token_count_or_ptr);
			s += word_len;
		}
	}
}

static void	copy_quote_word(char *s, int word_len, t_token *token)
{
	if (word_len <= 0)
		return ;
	while (token->word)
		token++;
	token->expand_char = *s;
	if (is_quote(*s) && word_len--)
		s++;
	token->word = malloc((word_len + 1) * sizeof(char));
	token->word[word_len] = '\0';
	while (word_len--)
		token->word[word_len] = s[word_len];
	(++token)->word = NULL;
}

static int	fill_tokens(char *s, int word_index, t_token **token_ptr)
{
	int	token_count;

	if (word_index <= 0)
		return (0);
	while (*token_ptr)
		token_ptr++;
	token_count = 1;
	tokenize_word(s, word_index, (void (*)()) incr_token_count, &token_count);
	*token_ptr = malloc(token_count * sizeof(t_token));
	if (*token_ptr == NULL)
		return (0);
	(*token_ptr)->word = NULL;
	tokenize_word(s, word_index, (void (*)()) copy_quote_word, *token_ptr);
	*++token_ptr = NULL;
	return (0);
}

t_token	**create_tokens(char *s)
{
	int		token_ptr_count;
	t_token	**tokens_ptr;

	token_ptr_count = 1;
	if (tokenize(s, incr_token_count, &token_ptr_count) == -1)
		return (NULL);
	tokens_ptr = malloc(token_ptr_count * sizeof(t_token *));
	if (tokens_ptr == NULL)
		return (NULL);
	*tokens_ptr = NULL;
	tokenize(s, (int (*)()) fill_tokens, tokens_ptr);
	return (tokens_ptr);
}
