#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	int		i;

	out = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (out == NULL)
		return (NULL);
	i = 0;
	while (*s1)
		out[i++] = *s1++;
	while (*s2)
		out[i++] = *s2++;
	out[i] = '\0';
	return (out);
}