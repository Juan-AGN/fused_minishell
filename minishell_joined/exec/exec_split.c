/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:18:29 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/13 11:18:31 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exteroided.h"

static int	ft_count_strings(const char*s, char c)
{
	size_t		i;
	int			a;
	size_t		len;

	i = 0;
	a = 0;
	len = exec_ft_strlen(s);
	while (i < len)
	{
		if (s[i] != c)
		{
			a++;
			while (s[i] != c && i < exec_ft_strlen (s))
				i++;
		}
		while (s[i] == c)
			i++;
	}
	return (a);
}

static void	ft_free(char **retorno, int i)
{
	while (i >= 0)
	{
		free(retorno[i]);
		retorno[i] = NULL;
		i--;
	}
	free(retorno);
}

static int	meter(const char*s, char c, char**retorno)
{
	size_t		i;
	int			a;
	int			start;

	i = 0;
	a = 0;
	while (i < exec_ft_strlen (s))
	{
		if (s[i] != c)
		{
			start = i;
			a++;
			while (s[i] != c && i < exec_ft_strlen (s))
				i++;
			retorno[a - 1] = exec_ft_substr (s, start, i - start);
			if (!(retorno[a - 1]))
			{
				ft_free(retorno, a - 1);
				return (0);
			}
		}
		while (s[i] == c)
			i++;
	}
	return (1);
}

char	**exec_split(char const *s, char c)
{
	int		num_strings;
	char	**retorno;
	int		bueno;

	if (!s)
		return (NULL);
	num_strings = ft_count_strings (s, c);
	retorno = malloc(sizeof(char *) * (num_strings + 1));
	if (!retorno)
		return (NULL);
	bueno = meter (s, c, retorno);
	if (!bueno)
	{
		free(retorno);
		return (NULL);
	}
	retorno[num_strings] = NULL;
	return (retorno);
}
