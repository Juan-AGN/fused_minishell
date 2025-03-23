/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:18:11 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/21 17:10:16 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exteroided.h"

char	**find_directories(char **envp, t_shell *shell)
{
	char	string_path[6];
	int		pos;
	char	**directories;
	char	*path_env;

	pos = 0;
	exec_ft_cpy(string_path, "PATH=", sizeof(string_path));
	while (envp[pos] != NULL)
	{
		if (e_ft_strncmp(string_path, envp[pos], 5) == 0)
		{
			path_env = envp[pos] + 5;
			directories = exec_split(path_env, ':');
			if (!directories)
			{
				perror("malloc error");
				builtin_exit(NULL, shell, -1);
			}
			return (directories);
		}
		pos++;
	}
	return (NULL);
}

char	*check_relative(const char *command, t_shell *shell)
{
	size_t	total_size;
	char	*full_path;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		builtin_exit(NULL, shell, -1);
	}
	total_size = exec_ft_strlen(cwd) + exec_ft_strlen(command) + 2;
	full_path = malloc(total_size);
	if (!full_path)
	{
		free(cwd);
		builtin_exit(NULL, shell, -1);
	}
	exec_ft_cpy(full_path, cwd, total_size);
	exec_ft_strlcat(full_path, "/", total_size);
	exec_ft_strlcat(full_path, command, total_size);
	free(cwd);
	return (full_path);
}

char	*build_path(const char *directory, const char *command, t_shell *shell)
{
	size_t	total_size;
	char	*full_path;

	if (command[0] == '/')
	{
		full_path = malloc(exec_ft_strlen(command) + 1);
		if (!full_path)
			return (NULL);
		exec_ft_cpy(full_path, command, exec_ft_strlen(command) + 1);
		return (full_path);
	}
	if (command[0] == '.' && (command[1] == '/' || command[1] == '.'))
		return (check_relative(command, shell));
	total_size = exec_ft_strlen(directory) + exec_ft_strlen(command) + 2;
	full_path = malloc(total_size);
	if (!full_path)
		return (NULL);
	exec_ft_cpy(full_path, directory, total_size);
	exec_ft_strlcat(full_path, "/", total_size);
	exec_ft_strlcat(full_path, command, total_size);
	return (full_path);
}

int	returning(int ncom, pid_t pid, t_shell *shell)
{
	int	i;
	int	wpid;
	int	exit_code;
	int	status;

	i = 0;
	while (i < ncom)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid < 0)
		{
			perror("waitpid");
			builtin_exit(NULL, shell, -1);
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
	return (exit_code);
}

void	here_doc_child(char *limiter, int fd)
{
	char	*line;
	size_t	limiter_len;

	limiter_len = exec_ft_strlen(limiter);
	while (1)
	{
		line = exec_get_next_line(0);
		if (!line)
			break ;
		if (e_ft_strncmp(line, limiter, limiter_len) == 0
			&& line[limiter_len] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, exec_ft_strlen(line));
		free(line);
	}
	return ;
}
