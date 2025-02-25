/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 12:11:03 by luialvar          #+#    #+#             */
/*   Updated: 2025/02/25 17:00:22 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strrjoin(char const *s1, char const *s2)
{
	char	*retorno;
	size_t	size;

	if (!s1 || !s2)
		return (0);
	size = ft_strllen(s1) + ft_strllen(s2);
	retorno = (char *)malloc(size + 1);
	if (!retorno)
		return (0);
	ft_memmcpy(retorno, s1, ft_strllen(s1));
	ft_memmcpy(retorno + ft_strllen(s1), s2, ft_strllen(s2));
	retorno[size] = '\0';
	return (retorno);
}

size_t	ft_strllen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	len = ft_strllen(s);
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

void	*ft_memmcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!src && !dest)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

size_t	ft_strllcpy(char *restrict dst, const char *restrict src, size_t size)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strllen((char *) src);
	if (size != 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}
