/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:20:34 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/13 11:20:35 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
void	builtin_echo(t_token *command)
{
	int	i;
	int	newline;
	int	j;

	i = 0;
	newline = 1;
	if (command->nparams == 0)
	{
		write(1, "\n", 1);
		return;
	}
	while (i < command->nparams && command->params[i][0] == '-')
	{
		j = 1;
		while (command->params[i][j] == 'n')
			j++;
		if (command->params[i][j] == '\0' && j > 1)
		{
			newline = 0;
			i++;
		}
		else
			break;
	}
	while (i < command->nparams)
	{
		write(1, command->params[i], ft_strrlen(command->params[i]));
		if (i < command->nparams - 1)
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}
