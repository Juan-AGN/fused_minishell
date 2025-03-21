/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxtokentwo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:38:11 by juan-ant          #+#    #+#             */
/*   Updated: 2025/03/21 13:26:05 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_ord_inout(t_shell *minishell, int i, t_token *token)
{
	char	**toret;
	int		u;

	u = 0;
	token->ninout = i;
	toret = malloc(sizeof(char *) * i);
	if (toret == NULL)
		return (ft_error_mini(minishell, -5, 0, 2));
	while (u != i)
	{
		toret[u] = NULL;
		u ++;
	}
	return (toret);
}

char	**ft_alloc_inout(t_shell *minishell, int i, t_token *token, int mod)
{
	char	**toret;
	int		u;

	u = 0;
	if (mod == 1)
		token->ninfiles = i;
	else
		token->noutfiles = i;
	toret = malloc(sizeof(char *) * i);
	if (toret == NULL)
		return (ft_error_mini(minishell, -5, 0, 2));
	while (u != i)
	{
		toret[u] = NULL;
		u ++;
	}
	return (toret);
}

void	ft_aux_in(t_shell *minishell, t_token *token, char *input, int i)
{
	int	u;
	int	o;

	u = 0;
	o = 0;
	if (token->infiles == NULL && minishell->error != -5)
		token->infiles = ft_alloc_inout(minishell, ft_inoutcounter(&input[i],
					'<'), token, 1);
	if (token->inout == NULL && minishell->error != -5)
		token->inout = ft_ord_inout(minishell, ft_inoutcounter(&input[i], '<')
				+ ft_inoutcounter(&input[i], '>'), token);
	if (token->infiles == NULL || token->inout == NULL
		|| minishell->error == -5)
		return ;
	while (token->ninfiles - ft_inoutcounter(&input[i], '<') > u)
		u ++;
	while (token->noutfiles - ft_inoutcounter(&input[i], '>') > o)
		o ++;
	token->infiles[u] = ft_handle_inf(minishell, &input[i]);
	token->inout[o + u] = token->infiles[u];
}

void	ft_aux_out(t_shell *minishell, t_token *token, char *input, int i)
{
	int	u;
	int	o;

	u = 0;
	o = 0;
	if (token->outfiles == NULL && minishell->error != -5)
		token->outfiles = ft_alloc_inout(minishell, ft_inoutcounter(&input[i],
					'>'), token, 2);
	if (token->inout == NULL && minishell->error != -5)
		token->inout = ft_ord_inout(minishell, ft_inoutcounter(&input[i], '<')
				+ ft_inoutcounter(&input[i], '>'), token);
	if (token->outfiles == NULL || token->inout == NULL
		|| minishell->error == -5)
		return ;
	while (token->noutfiles - ft_inoutcounter(&input[i], '>') > u)
		u ++;
	while (token->ninfiles - ft_inoutcounter(&input[i], '<') > o)
		o ++;
	token->outfiles[u] = ft_handle_out(minishell, &input[i]);
	token->inout[o + u] = token->outfiles[u];
}
