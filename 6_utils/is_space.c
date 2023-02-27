#include "../minishell.h"

int	is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\f'));
}