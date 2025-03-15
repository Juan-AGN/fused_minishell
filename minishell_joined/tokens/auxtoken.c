/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxtoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:41:23 by juan-ant          #+#    #+#             */
/*   Updated: 2025/03/15 17:15:36 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_count_token(char *input)
{
	int	i;

	i = 0;
	while (ft_specialchar_if(input[i]) != 1)
	{
		if (input[i] == '"')
		{
			i ++;
			while (input[i] != '"' && input[i] != '\0')
				i ++;
		}
		else if (input[i] == 39)
		{
			i ++;
			while (input[i] != 39 && input[i] != '\0')
				i ++;
		}
		if (ft_specialchar_if(input[i]) != 1)
			i ++;
	}
	return (i);
}

int	ft_count_inout(char *input)
{
	int	i;

	i = 0;
	while (input[i] == '<' || input[i] == '>')
		i ++;
	while (input[i] <= 32 && input[i] >= 1)
		i ++;
	i += ft_count_token(&input[i]);
	return (i);
}

int	ft_comands(char *input)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (input[i] != '\0')
	{
		while (input[i] <= 32 && input[i] >= 1)
			i ++;
		if (u == 0 && input[i] > 32)
			u ++;
		i += ft_count_token(&input[i]);
		i += ft_count_inout(&input[i]);
		if (input[i] == '|')
		{
			u ++;
			i ++;
		}
	}
	return (u);
}

int	ft_params(char *input)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (input[i] != '|' && input[i] != '\0')
	{
		while (input[i] <= 32 && input[i] >= 1)
			i ++;
		if (ft_spcharparams_if(input[i]) == 0)
			u ++;
		i += ft_count_token(&input[i]);
		if (input[i] == '<' || input[i] == '>')
			i += ft_count_inout(&input[i]);
	}
	return (u);
}

int	ft_inoutcounter(char *input, char tocount)
{
	int	i;
	int	u;

	i = 0;
	u = 0;
	while (input[i] != '|' && input[i] != '\0')
	{
		while (input[i] <= 32 && input[i] >= 1)
			i ++;
		i += ft_count_token(&input[i]);
		if (input[i] == '<' || input[i] == '>')
		{
			if (input[i] == tocount)
				u ++;
			i += ft_count_inout(&input[i]);
		}
	}
	return (u);
}
