/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_libft2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:28:19 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/13 11:28:22 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exteroided.h"

char	*exec_ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;

	if (!s)
		return (NULL);
	size = exec_ft_strlen (s);
	if (start >= size)
	{
		sub = malloc (1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (len + start > size)
	{
		len = size - start;
	}
	sub = (char *)malloc (len + 1);
	if (!sub)
		return (NULL);
	exec_ft_memcpy(sub, s + start, len);
	sub[len] = '\0';
	return (sub);
}

char	*exec_ft_strjoin(char const *s1, char const *s2)
{
	char	*retorno;
	size_t	size;

	if (!s1 || !s2)
		return (0);
	size = exec_ft_strlen(s1) + exec_ft_strlen(s2);
	retorno = (char *)malloc(size + 1);
	if (!retorno)
		return (0);
	exec_ft_memcpy(retorno, s1, exec_ft_strlen(s1));
	exec_ft_memcpy(retorno + exec_ft_strlen(s1), s2, exec_ft_strlen(s2));
	retorno[size] = '\0';
	return (retorno);
}

char	*exec_ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	len = exec_ft_strlen(s);
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

char	*exec_ft_strdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*dinamic;

	len = exec_ft_strlen(s1) + 1;
	i = 0;
	dinamic = (char *)malloc (len);
	if (!dinamic)
		return (NULL);
	while (i < len)
	{
		dinamic [i] = s1 [i];
		i++;
	}
	return (dinamic);
}
