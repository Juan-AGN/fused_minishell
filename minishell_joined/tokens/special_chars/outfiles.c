/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:04:24 by juan-ant          #+#    #+#             */
/*   Updated: 2025/03/21 13:21:12 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_handle_out(t_shell *minishell, char *input)
{
	int		type;

	type = 0;
	while (input[type] == '>')
		type ++;
	if (type > 2 || minishell->error == -5)
		return (NULL);
	input += type;
	while (*input >= 1 && *input <= 32)
		input ++;
	if (type == 1 && *input != '>' && *input != '|' && *input != '<'
		&& *input != '\0' && ft_params(input) != 0)
	{
		return (ft_handleplain(minishell, input, ">  "));
	}
	else if (type == 2 && *input != '>' && *input != '|' && *input != '<'
		&& *input != '\0' && ft_params(input) != 0)
	{
		return (ft_handleplain(minishell, input, ">> "));
	}
	else
		return (ft_error_mini(minishell, -1, 139, 0));
}
