/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 13:13:23 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/23 13:13:25 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	second_cd(char *oldpwd, t_shell *shell)
{
	write(2, "cd: too many arguments\n", 24);
	free(oldpwd);
	shell->cd_checker = 1;
	return ;
}

void	thrid_cd(char **path, t_env **env, char *oldpwd, t_shell *shell)
{
	*path = handle_cd_minus(*env);
	if (!(*path))
	{
		free(oldpwd);
		shell->cd_checker = 1;
		return ;
	}
	shell->cd_checker = 0;
	return ;
}
