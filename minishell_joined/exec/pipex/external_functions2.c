/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_functions2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:00:38 by luialvar          #+#    #+#             */
/*   Updated: 2025/02/25 17:25:38 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipes(int pipes[][2], int ncom)
{
	int	i;

	i = 0;
	while (i < ncom - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	check_argc_heredoc(int argc, char **argv) //checkeos iniciales
{
	int	fileout;

	fileout = 0;
	if (argc < 5)
	{
		perror("Invalid number of parameters");
		exit(EXIT_FAILURE);
	}
	if (ft_strnncmp("here_doc", argv[1], 8) == 0)
		fileout = 1;
	return (fileout);
}

void	here_doc_child(char *limiter, int fd)
{
	char	*line;
	size_t	limiter_len;

	limiter_len = ft_strllen(limiter);
	while (1)
	{
		line = get__next_line(0);
		if (!line)
			break ;
		if (ft_strnncmp(line, limiter, limiter_len) == 0
			&& line[limiter_len] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strllen(line));
		free(line);
	}
	exit(EXIT_SUCCESS);
}

void	returning(int *ncom_ishere, pid_t pid)
{
	int	i;
	int	wpid;
	int	exit_code;
	int	status;

	i = 0;
	while (i < ncom_ishere[0])
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid < 0)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (wpid == pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else
				exit_code = 1;
		}
		i++;
	}
	exit(exit_code);
}
