/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_functions3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:17:52 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/23 21:17:54 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exteroided.h"

void	do_concat(char **envp, t_env *tmp, size_t len, int *i)
{
	exec_ft_strlcat(envp[*i], tmp->name, len);
	exec_ft_strlcat(envp[*i], "=", len);
	exec_ft_strlcat(envp[*i], tmp->content, len);
	(*i)++;
}

void	loop_converting(t_env *tmp, char **envp, t_shell *shell)
{
	size_t	len;
	int		j;
	int		i;

	i = 0;
	while (tmp)
	{
		if (tmp->content[0] != '\0')
		{
			len = exec_ft_strlen(tmp->name) + exec_ft_strlen(tmp->content) + 2;
			envp[i] = (char *)malloc(len);
			if (!envp[i])
			{
				j = i;
				while (--j >= 0)
					free(envp[j]);
				free(envp);
				builtin_exit(NULL, shell, -1);
			}
			envp[i][0] = '\0';
			do_concat(envp, tmp, len, &i);
		}
		tmp = tmp->next;
	}
	envp[i] = NULL;
}

char	**exec_convert_env_to_array(t_shell *shell)
{
	int		count;
	t_env	*tmp;
	char	**envp;

	tmp = *(shell->env);
	count = 0;
	while (tmp)
	{
		if (tmp->content[0] != '\0')
			count++;
		tmp = tmp->next;
	}
	envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!envp)
	{
		perror("malloc error");
		builtin_exit(NULL, shell, -1);
	}
	tmp = *(shell->env);
	loop_converting(tmp, envp, shell);
	return (envp);
}

void	exec_free_array(char **directories)
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

void	create_pipes(int pipes[][2], int ncom, t_shell *shell)
{
	int	i;

	i = 0;
	while (i < ncom - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe errpr");
			builtin_exit(NULL, shell, -1);
		}
		i++;
	}
}
