/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleplain.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:39:23 by juan-ant          #+#    #+#             */
/*   Updated: 2025/03/18 18:59:31 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_joinenv_plain(t_shell *minishell, char *str, char *tojoin)
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
	return (joined);
}

char	*ft_joiner(t_shell *minishell, char *str, char *tojoin)
{
	char	*joined;
	char	*res;

	if (str[0] == 39)
		res = ft_handlesingles(minishell, &str[1]);
	else if (str[0] == 34)
		res = ft_handledoubles(minishell, &str[1], NULL);
	else if (str[0] == '$')
		res = ft_joinenv_plain(minishell, &str[1], NULL);
	else
		res = "";
	if (res == NULL)
	{
		free(tojoin);
		return (NULL);
	}
	joined = ft_strjoin(tojoin, res);
	free(tojoin);
	free(res);
	return (joined);
}

int	ft_conditional_plain(char *str, int i)
{
	if (str[i] == 34 || (str[i] >= 0 && str[i] <= 32) || str[i] == '$'
		|| str[i] == 39 || str[i] == '>' || str[i] == '<' || str[i] == '|')
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

char	*ft_plain_cases(t_shell *minishell, char *str, char *tojoin)
{
	int		i;
	char	*res;

	i = 1;
	res = ft_joiner(minishell, str, tojoin);
	if (res == NULL)
		return (ft_error_mini(minishell, -5, 0, 2));
	if (str[0] == '$')
		i += ft_return_lenght(str + i);
	else
	{
		while (str[i] != str[0] && str[i] != '\0')
			i ++;
		if (str[i] == '\0' && (str[0] == 39 || str[0] == 34))
			minishell->error = 1;
		i ++;
	}
	tojoin = ft_handleplain(minishell, &str[i], res);
	free(res);
	return (tojoin);
}

char	*ft_handleplain(t_shell *minishell, char *str, char *tojoin)
{
	int		i;
	char	*current;
	char	*joined;

	i = 0;
	while (ft_conditional_plain(str, i) != 1)
		i ++;
	current = malloc(sizeof(char) * (i + 1));
	if (current == NULL)
		return (ft_error_mini(minishell, -5, 0, 2));
	ft_strlcpy(current, str, i + 1);
	joined = ft_strjoin(tojoin, current);
	free(current);
	if (joined == NULL)
		return (ft_error_mini(minishell, -5, 0, 2));
	if (ft_spcharparams_if(str[i]) == 0)
		joined = ft_plain_cases(minishell, &str[i], joined);
	return (joined);
}
