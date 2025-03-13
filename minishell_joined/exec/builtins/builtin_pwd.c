/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:21:20 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/13 11:21:22 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0); // Solicita memoria dinámica para almacenar el directorio actual
	if (cwd != NULL)
	{
		write(1, cwd, ft_strrlen(cwd));
		write(1, "\n", 1);
		free(cwd);
	}
	else
		perror("pwd");
}
