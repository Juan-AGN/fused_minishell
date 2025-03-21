/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_functions_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:16:48 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/20 11:16:51 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*ft_sstrdup(const char *s1)
{
	size_t	len;
	size_t	i;
	char	*dinamic;

	len = ft_strrlen(s1) + 1;
	i = 0;
	dinamic = ft_ccalloc (len, 1);
	if (!dinamic)
		return (NULL);
	while (i < len)
	{
		dinamic [i] = s1 [i];
		i++;
	}
	return (dinamic);
}

void	*ft_ccalloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc (count * size);
	if (!ptr)
		return (0);
	ft_bbzero(ptr, size * count);
	return (ptr);
}

void	ft_bbzero(void *s, size_t n)
{
	ft_mmemset (s, 0, n);
}

void	*ft_mmemset(void *s, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)s)[i] = (unsigned char) c;
		i++;
	}
	return (s);
}

/* Verificar si un identificador es válido */
int	is_valid_identifier(const char *str)
{
	if (!str || *str == '\0' || !(ft_iisalpha(*str) || *str == '_'))
		return (0);
	str++;
	while (*str)
	{
		if (!(ft_iisalnum(*str) || *str == '_'))
			return (0);
		str++;
	}
	return (1);
}
