/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:42:54 by juan-ant          #+#    #+#             */
/*   Updated: 2024/08/04 17:11:58 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_bnldup(char *s1)
{
	char	*str;

	if (!*s1)
		return (NULL);
	str = malloc(ft_bnllen(s1) * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	ft_bnlcpy(str, s1);
	return (str);
}

void	ft_bnlcpy(char *dst, char *src)
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

char	*ft_bnljoin(char *s1, char *s2)
{
	char	*ret;

	ret = malloc(1 + ft_bnllen(s1) + ft_bnllen(s2) * sizeof(char));
	if (ret == NULL)
		return (ft_bnleing(s1, s2, ret));
	ft_bnlcpy(ret, s1);
	ret = ret + ft_bnllen(s1);
	ft_bnlcpy(ret, s2);
	ret = ret - ft_bnllen(s1);
	ft_bnleing(s1, s2, NULL);
	return (ret);
}

char	*ft_bnlchr(char *s)
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

size_t	ft_bnllen(char *str)
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
