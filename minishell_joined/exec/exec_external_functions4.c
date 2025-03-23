/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_functions4.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:18:07 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/23 21:18:13 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exteroided.h"

void	do_token_func(const t_token *token, size_t *total_length)
{
	int	i;

	i = 0;
	while (i < token->nparams)
	{
		*total_length += 1;
		*total_length += exec_ft_strlen(token->params[i]);
		i++;
	}
	*total_length += 1;
}

char	*token_to_str(const t_token *token, t_shell *shell)
{
	size_t	total_length;
	int		i;
	char	*result;

	if (!token || !token->command)
		return (NULL);
	total_length = exec_ft_strlen(token->command);
	i = 0;
	do_token_func(token, &total_length);
	result = (char *)malloc(total_length);
	if (!result)
	{
		perror("malloc errpr");
		builtin_exit(NULL, shell, -1);
	}
	result[0] = '\0';
	exec_ft_strlcat(result, token->command, total_length);
	i = 0;
	while (i < token->nparams)
	{
		exec_ft_strlcat(result, " ", total_length);
		exec_ft_strlcat(result, token->params[i], total_length);
		i++;
	}
	return (result);
}

int	has_slash(char *str)
{
	while (*str)
	{
		if (*str == '/')
			return (1);
		str++;
	}
	return (0);
}

void	checkdirec(char *cmd, char *full_path, char **commands, t_shell *shell)
{
	struct stat	st;

	if (stat(cmd, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			write(STDERR_FILENO, cmd, exec_ft_strlen(cmd));
			write(STDERR_FILENO, ": Is a directory\n", 17);
			free(full_path);
			free_array(commands);
			builtin_exit(NULL, shell, 126);
		}
	}
}

void	try(char *full_path, char **commands, t_shell *shell, char **envp)
{
	struct stat	st;

	if (has_slash(commands[0]))
		checkdirec(commands[0], full_path, commands, shell);
	if (stat(full_path, &st) == 0)
	{
		if (st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
		{
			execve(full_path, commands, envp);
			perror("execve error");
			free(full_path);
			free_array(commands);
			builtin_exit(NULL, shell, 126);
		}
		write(STDERR_FILENO, full_path, exec_ft_strlen(full_path));
		write(STDERR_FILENO, ": Permission denied\n", 20);
		free(full_path);
		free_array(commands);
		builtin_exit(NULL, shell, 126);
	}
	free(full_path);
}
