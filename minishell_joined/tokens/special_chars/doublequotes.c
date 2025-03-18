/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doublequotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 10:31:23 by juan-ant          #+#    #+#             */
/*   Updated: 2025/03/18 13:43:35 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_strjoinenv(t_shell *minishell, char *tojoin, char *env)
{
	char	*env_content;

	env_content = ft_plstsearch(minishell->env[0], env, minishell);
	free(env);
	return (ft_strjoin(tojoin, env_content));
}

int	ft_return_lenght(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (i + 1);
	if (str[i] == '$')
		return (i + 1);
	while (str[i] != 34 && str[i] != '\0' && str[i] != '$' && str[i] != 39
		&& str[i] != ' ' && str[i] != '|' && str[i] != '<'
		&& str[i] != '>')
	{
		i ++;
	}
	return (i);
}

char	*ft_joinenv_doubles(t_shell *minishell, char *str, char *tojoin)
{
	int		i;
	char	*env;
	char	*joined;

	i = ft_return_lenght(str);
	env = malloc(sizeof(char) * (i + 1));
	if (env == NULL)
		return (ft_error_mini(minishell, -5, 0, 2));
	ft_strlcpy(env, str, i + 1);
	joined = ft_strjoinenv(minishell, tojoin, env);
	if (joined == NULL)
		return (ft_error_mini(minishell, -5, 0, 2));
	if ((str[i] != '"' && str[i] != '\0') || str[i] == '$')
		env = joined;
	if (str[i] != '"' && str[i] != '\0')
		joined = ft_handledoubles(minishell, &str[i], env);
	if ((str[i] != '"' && str[i] != '\0') || str[i] == '$')
		free(env);
	return (joined);
}

int	ft_conditional_double(char *str, int i)
{
	if (str[i] == 34 || str[i] == '\0' || str[i] == '$')
	{
		if (str[i] == '$')
		{
			if (str[i + 1] <= 32 && str[i + 1] >= 0)
				return (0);
		}
		return (1);
	}
	return (0);
}

char	*ft_handledoubles(t_shell *minishell, char *str, char *tojoin)
{
	int		i;
	char	*current;
	char	*joined;

	i = 0;
	while (ft_conditional_double(str, i) != 1)
		i ++;
	current = malloc(sizeof(char) * (i + 1));
	if (current == NULL)
		return (ft_error_mini(minishell, -5, 0, 2));
	ft_strlcpy(current, str, i + 1);
	joined = ft_strjoin(tojoin, current);
	free(current);
	if (joined == NULL)
		return (ft_error_mini(minishell, -5, 0, 2));
	if (str[i] == '$')
	{
		current = joined;
		joined = ft_joinenv_doubles(minishell, &str[i + 1], current);
		free(current);
	}
	return (joined);
}
