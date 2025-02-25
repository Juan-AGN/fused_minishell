/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxtokenifs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:41:23 by juan-ant          #+#    #+#             */
/*   Updated: 2025/01/02 18:48:26 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_specialchar_if(char c)
{
	if (c > 32 && c != '<' && c != '>' && c != '|')
		return (0);
	else
		return (1);
}

int	ft_spcharparams_if(char c)
{
	if (c != '<' && c != '>' && c != '|' && c > 32)
		return (0);
	else
		return (1);
}
