/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sciftci <sciftci@student.42kocaeli.com.tr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 04:28:29 by sciftci           #+#    #+#             */
/*   Updated: 2023/02/28 04:28:30 by sciftci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		while (tokens[i][j].word)
			free(tokens[i][j++].word);
		free(tokens[i]);
	}
	free(tokens);
	return (1);
}
