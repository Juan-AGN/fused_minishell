/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:54:45 by luialvar          #+#    #+#             */
/*   Updated: 2025/02/25 17:25:36 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free__array(char **directories)
{
	int	i;

	i = 0;
	while (directories[i] != NULL)
	{
		free(directories[i]);
		i++;
	}
	free(directories);
}

size_t	ft_strllcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (dst[len] && len < size)
		len++;
	while (src[i] && (len + i + 1) < size)
	{
		dst[len + i] = src[i];
		i++;
	}
	if (len < size)
		dst[len + i] = '\0';
	return (len + ft_strllen(src));
}

/* 
Da las posibles rutas donde se pueden encontrar los archivos ejecutables
dentro de PATH
*/
char	**find_directories(char **envp)
{
	char	string_path[6];
	int		pos;
	char	**directories;
	char	*path_env;

	pos = 0;
	ft_strllcpy(string_path, "PATH=", sizeof(string_path));
	while (envp[pos] != NULL)
	{
		if (ft_strnncmp(string_path, envp[pos], 5) == 0)
		{
			path_env = envp[pos] + 5;
			directories = ft_ssplit_exec(path_env, ':');
			if (!directories)
			{
				perror("malloc error");
				exit(EXIT_FAILURE);
			}
			return (directories);
		}
		pos++;
	}
	perror("No path defined");
	exit(EXIT_FAILURE);
}

char	*build_full_path(const char *directory, const char *command)
{
	size_t	total_size;
	char	*full_path;

	total_size = ft_strllen(directory) + ft_strllen(command) + 2;
	full_path = malloc(total_size);
	if (!full_path)
		return (NULL);
	ft_strllcpy(full_path, directory, total_size);
	ft_strllcat(full_path, "/", total_size);
	ft_strllcat(full_path, command, total_size);
	return (full_path);
}
