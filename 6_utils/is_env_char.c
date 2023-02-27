
#include "../minishell.h"

int	is_env_char(char c)
{
    return (ft_isalpha(c) || ft_isdigit(c) || c == '_');
}