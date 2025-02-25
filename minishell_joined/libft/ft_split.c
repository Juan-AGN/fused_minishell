/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:24:43 by juan-ant          #+#    #+#             */
/*   Updated: 2023/10/01 14:29:18 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	i;

	i = 1;
	while (*s)
	{
		if (*s && c != *s)
			i++;
		while (*s && c != *s)
			s++;
		if (*s)
			s++;
	}
	return (i);
}

static char	**ft_freeing(char **arr, int i)
{
	while (i != -1)
	{
		free(arr[i]);
		i --;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**arr;
	char	*start;

	i = 0;
	arr = ft_calloc(ft_count(s, c), sizeof(char *));
	if (arr == NULL)
		return (NULL);
	while (*s && s != NULL)
	{
		if (*s && c != *s)
		{
			start = (char *)s;
			while (*s && c != *s)
				s ++;
			arr[i] = ft_substr(start, 0, ft_strlen(start) - ft_strlen(s));
			if (arr[i] == NULL)
				return (ft_freeing(arr, i));
			i ++;
		}
		if (*s)
			s++;
	}
	arr[i] = NULL;
	return (arr);
}
