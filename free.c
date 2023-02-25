
int	free_argv(char **argv)
{
	int	i;

	i = -1;
	while (argv[++i])
		free(argv[i]);
	free(argv);
	return (0);
}

/*
** can it be just argv?
*/
int	free_redirections(t_redirection *redir)
{
	int	i;

	i = -1;
	while (redir[++i].value)
		free(redir[i].value);
	free(redir);
	return (0);
}

int	free_tokens(t_token **tokens)
{
	int	i;
	int	j;

	i = -1;
	while (tokens[++i])
	{
		j = 0;
		while (tokens[i][j].value)
			free(tokens[i][j++].value);
		free(tokens[i]);
	}
	free(tokens);
	return (1);
}
