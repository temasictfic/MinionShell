#include "libft.h"

char	*ft_itoa(int n)
{
	int			i;
	static char	res[13];
	int			neg;

	i = 13;
	res[--i] = '\0';
	neg = 0;
	if (n < 0)
		neg = 1;
	else
		n = -n;
	while (1)
	{
		res[--i] = '0' - n % 10;
		n /= 10;
		if (!n)
			break ;
	}
	if (neg)
		res[--i] = '-';
	return (res + i);
}
