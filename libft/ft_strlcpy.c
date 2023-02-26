#include "libft.h"

unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int size)
{
	unsigned int	i;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (--size && *src && ++i)
		*dst++ = *src++;
	*dst = '\0';
	while (*src++)
		i++;
	return (i);
}