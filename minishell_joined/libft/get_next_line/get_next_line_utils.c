/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:42:54 by juan-ant          #+#    #+#             */
/*   Updated: 2024/08/04 17:13:00 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_gnldup(char *s1)
{
	char	*str;

	if (!*s1)
		return (NULL);
	str = malloc(ft_gnllen(s1) * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	ft_gnlcpy(str, s1);
	return (str);
}

void	ft_gnlcpy(char *dst, char *src)
{
	if (src != NULL)
	{
		while (*src)
		{
			*dst = *src;
			dst ++;
			src ++;
		}
		*dst = '\0';
	}
}

char	*ft_gnljoin(char *s1, char *s2)
{
	char	*ret;

	ret = malloc(1 + ft_gnllen(s1) + ft_gnllen(s2) * sizeof(char));
	if (ret == NULL)
		return (ft_gnleing(s1, s2, ret));
	ft_gnlcpy(ret, s1);
	ret = ret + ft_gnllen(s1);
	ft_gnlcpy(ret, s2);
	ret = ret - ft_gnllen(s1);
	ft_gnleing(s1, s2, NULL);
	return (ret);
}

char	*ft_gnlchr(char *s)
{
	if (s == NULL)
		return (NULL);
	while (*s && s != NULL)
	{
		if (s)
			if (*s == '\n')
				return (s);
		s ++;
	}
	return (NULL);
}

size_t	ft_gnllen(char *str)
{
	size_t	n;

	n = 0;
	if (str == NULL)
		return (0);
	if (!*str)
		return (0);
	while (*str && str != NULL)
	{
		n ++;
		str ++;
	}
	return (n);
}
