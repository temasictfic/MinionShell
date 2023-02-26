#include "libft.h"

char	*ft_strdup(char *str)
{
	char	*s;
	int		len;

	len = ft_strlen(str) + 1;
	s = malloc(len * sizeof(char));
	ft_strlcpy(s, str, len);
	return (s);
}
