/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_preparation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:23:02 by juan-ant          #+#    #+#             */
/*   Updated: 2025/03/20 16:16:46 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*ft_dup_env(char *name)
{
	char	*raw_content;
	char	*dupped;
	t_env	*list;

	raw_content = getenv(name);
	if (raw_content != NULL)
	{
		dupped = ft_strdup(raw_content);
		if (dupped == NULL)
			return (NULL);
	}
	else
		dupped = NULL;
	list = ft_plstnew(name, dupped);
	if (list == NULL)
	{
		free(name);
		free(dupped);
		return (NULL);
	}
	return (list);
}

int	ft_count_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		i ++;
		envp ++;
	}
	return (i);
}

int	ft_prep_env(char **envp, t_shell *minishell)
{
	int		i;
	t_env	*aux;
	char	*name;

	i = 1;
	name = ft_get_env(*envp);
	if (name == NULL)
		return (-1);
	minishell->env[0] = ft_dup_env(name);
	if (minishell->env[0] == NULL)
		return (ft_plstclear(minishell->env));
	while (envp[i] != NULL)
	{
		name = ft_get_env(envp[i]);
		if (name == NULL)
			return (-1);
		aux = ft_dup_env(name);
		if (aux == NULL)
			return (ft_plstclear(minishell->env));
		ft_plstadd_back(minishell->env, aux);
		i ++;
	}
	return (0);
}

char	*ft_get_env(char *str)
{
	int		i;
	char	*toreturn;

	i = ft_strlen(str) - ft_strlen(ft_strchr(str, '='));
	if (i == -1)
		return (NULL);
	toreturn = ft_strndup(str, i);
	if (toreturn == NULL)
		return (NULL);
	return (toreturn);
}

t_shell	*ft_prepare_values(char **envp)
{
	t_shell		*minishell;

	minishell = malloc(sizeof(t_shell));
	if (minishell == NULL)
		return (NULL);
	minishell->env = malloc(sizeof(t_env *) * ft_count_env(envp));
	if (minishell->env == NULL)
		return (ft_mass_free(minishell, NULL, NULL, NULL));
	if (ft_prep_env(envp, minishell) == -1)
		return (ft_mass_free(minishell, minishell->token, NULL, NULL));
	minishell->error = 0;
	minishell->exit_code = ft_itoa(0);
	if (minishell->exit_code == NULL)
	{
		ft_plstclear(minishell->env);
		return (ft_mass_free(minishell, minishell->token,
				minishell->env, NULL));
	}
	minishell->input = NULL;
	minishell->envp = NULL;
	minishell->pipes = NULL;
	minishell->token = NULL;
	return (minishell);
}
