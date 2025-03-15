/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxtokenifs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:41:23 by juan-ant          #+#    #+#             */
/*   Updated: 2025/03/15 17:15:37 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_specialchar_if(char c)
{
	if ((c > 32 || c < 0) && c != '<' && c != '>' && c != '|')
		return (0);
	else
		return (1);
}

int	ft_spcharparams_if(char c)
{
	if (c != '<' && c != '>' && c != '|' && (c > 32 || c < 0))
		return (0);
	else
		return (1);
}
