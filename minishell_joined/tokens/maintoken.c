/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintoken.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:41:23 by juan-ant          #+#    #+#             */
/*   Updated: 2025/03/19 19:49:18 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_in_out(t_shell *minishell, t_token *token, char *input, int i)
{
	if (input[i] == '<')
		ft_aux_in(minishell, token, input, i);
	else if (input[i] == '>')
		ft_aux_out(minishell, token, input, i);
	return (ft_count_inout(&input[i]) + i);
}

int	ft_createcommand(t_shell *minishell, t_token *token, char *input, int i)
{
	int	u;

	u = 0;
	if (token->command == NULL)
	{
		token->command = ft_handleplain(minishell, &input[i], NULL);
		i += ft_count_token(&input[i]);
		token->nparams = ft_params(&input[i]);
		token->params = ft_safe_malloc(sizeof(char *)
				* token->nparams, minishell);
		if (token->command == NULL)
			return (i);
	}
	else
	{
		while (token->nparams - ft_params(&input[i]) > u)
			u ++;
		token->params[u] = ft_handleplain(minishell, &input[i], NULL);
		i += ft_count_token(&input[i]);
		if (token->params[u] == NULL)
			return (i + ft_count_token(&input[i]));
	}
	return (i);
}

int	ft_alloctoken(int i, t_shell *minishell)
{
	int	u;

	u = 0;
	minishell->ncomands = i;
	minishell->token = malloc(sizeof(t_token) * i);
	if (minishell->token == NULL)
		return (ft_error_mini_n(minishell, -5, 0, 2));
	while (u < i)
	{
		minishell->token[u].command = NULL;
		minishell->token[u].params = NULL;
		minishell->token[u].infiles = NULL;
		minishell->token[u].outfiles = NULL;
		minishell->token[u].inout = NULL;
		minishell->token[u].nparams = 0;
		minishell->token[u].ninfiles = 0;
		minishell->token[u].noutfiles = 0;
		minishell->token[u].ninout = 0;
		u ++;
	}
	return (1);
}

int	ft_maintoken_loop(t_shell *minishell, char *input, int i, int u)
{
	while (input[i] != '\0')
	{
		if (ft_spcharparams_if(input[i]) == 0)
			i = ft_createcommand(minishell, &minishell->token[u], input, i);
		while (input[i] >= 1 && input[i] <= 32)
			i ++;
		if (input[i] == '<' || input[i] == '>')
			i = ft_in_out(minishell, &minishell->token[u], input, i);
		if (input[i] == '|')
		{
			if (minishell->token[u].command == NULL
				&& minishell->token[u].infiles == NULL
				&& minishell->token[u].outfiles == NULL)
				return (ft_printf("Error\n"));
			u ++;
			i ++;
		}
	}
	if (minishell->token[u].command == NULL
		&& minishell->token[u].infiles == NULL
		&& minishell->token[u].outfiles == NULL)
		return (ft_printf("Error\n"));
	return (0);
}

int	ft_maintoken(t_shell *minishell, char *input)
{
	if (ft_comands(input) == 0)
		return (1);
	ft_alloctoken(ft_comands(input), minishell);
	return (ft_maintoken_loop(minishell, input, 0, 0));
}
