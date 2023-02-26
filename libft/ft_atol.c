#include "libft.h"

int	ft_atol(const char *nptr, long *v)
{
	int	neg;

	*v = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	neg = *nptr == '-';
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	if (!*nptr)
		return (0);
	while (*nptr >= '0' && *nptr <= '9')
		if (*v * 10 - *nptr + '0' > *v)
			return (0);
	else
		*v = *v * 10 - *nptr++ + '0';
	if (!neg && *v < *v - 1)
		return (0);
	if (!neg)
		*v = -*v;
	if (*nptr)
		return (0);
	return (1);
}
