/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxtokentwo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:38:11 by juan-ant          #+#    #+#             */
/*   Updated: 2025/01/29 16:44:24 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_alloc_inout(int i, t_token *token, int mod)
{
	char	**toret;
	int		u;

	u = 0;
	if (mod == 1)
		token->ninfiles = i;
	else
		token->noutfiles = i;
	toret = malloc(sizeof(char **) * i);
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

	u = 0;
	if (token->infiles == NULL)
	{
		token->infiles = ft_alloc_inout(ft_inoutcounter(&input[i],
					'<'), token, 1);
	}
	while (token->ninfiles - ft_inoutcounter(&input[i], '<') > u)
		u ++;
	token->infiles[u] = ft_handle_inf(minishell, &input[i]);
}

void	ft_aux_out(t_shell *minishell, t_token *token, char *input, int i)
{
	int	u;

	u = 0;
	if (token->outfiles == NULL)
	{
		token->outfiles = ft_alloc_inout(ft_inoutcounter(&input[i],
					'>'), token, 2);
	}
	while (token->noutfiles - ft_inoutcounter(&input[i], '>') > u)
		u ++;
	token->outfiles[u] = ft_handle_out(minishell, &input[i]);
}
