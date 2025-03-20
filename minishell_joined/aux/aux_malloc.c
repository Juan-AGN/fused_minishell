/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:11:36 by juan-ant          #+#    #+#             */
/*   Updated: 2025/03/20 16:20:36 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	*ft_safe_malloc(int n, t_shell *minishell)
{
	char	*toret;

	if (n == 0)
		return (NULL);
	toret = malloc(n);
	if (toret == NULL)
		ft_error_mini(minishell, -5, 0, 2);
	return (toret);
}

void	*ft_error_mini(t_shell *minishell, int err, int ex_cod, int mod)
{
	if (mod != 1)
		minishell->error = err;
	if (mod != 2)
	{
		ft_free(minishell->exit_code);
		minishell->exit_code = ft_itoa(ex_cod);
		if (minishell->exit_code == NULL)
			minishell->error = -5;
	}
	return (NULL);
}

int	ft_error_mini_n(t_shell *minishell, int err, int ex_cod, int mod)
{
	if (mod != 1)
		minishell->error = err;
	if (mod != 2)
	{
		ft_free(minishell->exit_code);
		minishell->exit_code = ft_itoa(ex_cod);
		if (minishell->exit_code == NULL)
			minishell->error = -5;
	}
	return (-1);
}
