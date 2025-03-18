/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenfree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:35:38 by juan-ant          #+#    #+#             */
/*   Updated: 2025/03/18 19:11:00 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_params(int nparams, t_token *token)
{
	while (nparams != -1)
	{
		if (token->params[nparams] != NULL)
			free(token->params[nparams]);
		nparams --;
	}
	if (token->params != NULL)
		free(token->params);
}

void	ft_free_in(int ninfiles, t_token *token)
{
	while (ninfiles != -1)
	{
		if (token->infiles != NULL)
			if (token->infiles[ninfiles] != NULL)
				free(token->infiles[ninfiles]);
		ninfiles --;
	}
	if (token->infiles != NULL)
		free(token->infiles);
}

void	ft_free_out(int noutfiles, t_token *token)
{
	while (noutfiles != -1)
	{
		if (token->outfiles != NULL)
			if (token->outfiles[noutfiles] != NULL)
				free(token->outfiles[noutfiles]);
		noutfiles --;
	}
	if (token->outfiles != NULL)
		free(token->outfiles);
}

void	ft_free_tokens(t_shell *minishell, t_token *token)
{
	int	commands;

	commands = minishell->ncomands - 1;
	if (token != NULL)
	{
		while (commands != -1)
		{
			if (token[commands].command != NULL)
				free(token[commands].command);
			ft_free_params(token[commands].nparams - 1, &token[commands]);
			ft_free_in(token[commands].ninfiles - 1, &token[commands]);
			ft_free_out(token[commands].noutfiles - 1, &token[commands]);
			if (token[commands].inout != NULL)
				free(token[commands].inout);
			commands --;
		}
		free(token);
		minishell->token = NULL;
	}
}
