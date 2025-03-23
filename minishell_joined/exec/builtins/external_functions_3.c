/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_functions_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:17:46 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/20 11:17:48 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_iisdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

char	*ft_sstrchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	len = ft_strrlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == (char)c)
		{
			return ((char *)s + i);
		}
		i++;
	}
	return (NULL);
}

int	ft_iisalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
	{
		return (1);
	}
	return (0);
}

int	ft_iisalnum(int c)
{
	if (ft_iisalpha(c) || (ft_iisdigit(c)))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

size_t	e(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
