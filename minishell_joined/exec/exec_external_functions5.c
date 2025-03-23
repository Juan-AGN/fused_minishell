/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_functions5.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:18:24 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/23 21:18:26 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exteroided.h"

char	**handle_params_allocation(char *command, t_shell *shell)
{
	char	**commands;

	commands = exec_split(command, ' ');
	if (!commands)
	{
		perror("malloc error");
		builtin_exit(NULL, shell, 1);
	}
	return (commands);
}

/*
Se le pasa el comando entero junto a sus posibles parametros de ejecucion,
las rutas donde es posible que se encuentre y envp

*/
void	execute(char *command, char **directories, char **envp, t_shell *shell)
{
	char	**params;
	char	*full_path;
	int		i;

	params = handle_params_allocation(command, shell);
	free(command);
	i = 0;
	while (directories[i] != NULL)
	{
		full_path = build_path(directories[i], params[0], shell);
		if (!full_path)
		{
			free_array(params);
			perror("malloc error");
			builtin_exit(NULL, shell, 1);
		}
		try(full_path, params, shell, envp);
		i++;
	}
	write(STDERR_FILENO, params[0], exec_ft_strlen(params[0]));
	write(STDERR_FILENO, ": command not found\n", 20);
	free_array(params);
	builtin_exit(NULL, shell, 127);
}
