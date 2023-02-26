#include "minishell.h"

int	is_redir(char *s, int redir_count)
{
	if (redir_count == 1 && (s[0] == '<' || s[0] == '>'))
		return (1);
	if (redir_count == 2 && ((*s == '<' && s[1] == '<') || (*s == '>' && s[1] == '>')))
		return (1);
	return (0);
}
