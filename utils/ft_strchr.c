#include "minishell.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = -1;
	while (str[++i] != (unsigned char)c)
		if (str[i] == '\0')
			return (NULL);
	return ((char *)str + i);
}