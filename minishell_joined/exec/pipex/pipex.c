/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:47:03 by luialvar          #+#    #+#             */
/*   Updated: 2025/02/25 17:26:08 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	try(char *full_path, char **commands, char **directories, char **envp)
{
	if (access(full_path, X_OK) == 0)
	{
		execve(full_path, commands, envp);
		perror("execve error");
		free(full_path);
		free__array(commands);
		free__array(directories);
		exit(EXIT_FAILURE);
	}
	free(full_path);
}

char	**handle_params_allocation(char *command, char **directories)
{
	char	**commands;

	commands = ft_ssplit_exec(command, ' ');
	if (!commands)
	{
		perror("malloc error");
		free__array(directories);
		exit(EXIT_FAILURE);
	}
	return (commands);
}

void	execute(char *command, char **directories, char **envp)
{
	char	**params;
	char	*full_path;
	int		i;

	params = handle_params_allocation(command, directories);
	i = 0;
	while (directories[i] != NULL)
	{
		full_path = build_full_path(directories[i], params[0]);
		if (!full_path)
		{
			free__array(params);
			free__array(directories);
			perror("malloc error");
			exit(EXIT_FAILURE);
		}
		try(full_path, params, directories, envp);
		i++;
	}
	free__array(params);
	free__array(directories);
	write(STDERR_FILENO, command, ft_strllen(command));
	write(STDERR_FILENO, ": command not found\n", 20);
	exit(127);
}
/*
int	main(int argc, char **argv, char **envp)
{
	int		is_here_doc;
	char	**directories;
	int		ncom_isheredoc[2];

	is_here_doc = check_argc_heredoc(argc, argv);
	directories = find_directories(envp);
	if (!directories)
	{
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	ncom_isheredoc[0] = argc - 3;
	ncom_isheredoc[1] = is_here_doc;
	run(argv, directories, envp, ncom_isheredoc);
}*/
