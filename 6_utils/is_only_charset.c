#include "../minishell.h"

int	is_only_charset(const char *s, char *charset)
{
	while (*s)
		if (ft_strchr(charset, *s++) == NULL)
			return (0);
	return (1);
}