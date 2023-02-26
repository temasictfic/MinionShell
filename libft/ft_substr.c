#include "libft.h"

char	*ft_substr(char *s, int n)
{
	char	*out;

	out = malloc((n + 1) * sizeof(char));
	out[n] = '\0';
	while (n--)
		out[n] = s[n];
	return (out);
}

