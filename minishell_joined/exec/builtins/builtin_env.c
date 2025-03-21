/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:20:46 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/13 11:20:48 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_env(int nparams, char **envp)
{
	int		i;
	char	*equal_sign;

	if (nparams != 0)
		return (127);
	i = 0;
	while (envp[i])
	{
		equal_sign = ft_sstrchr(envp[i], '=');
		if (equal_sign)
		{
			write(1, envp[i], ft_strrlen(envp[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}
