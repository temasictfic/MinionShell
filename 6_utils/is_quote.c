#include "../minishell.h"

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}