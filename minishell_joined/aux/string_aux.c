/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:42:50 by juan-ant          #+#    #+#             */
/*   Updated: 2025/03/21 13:30:59 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strndup(const char *s1, int n)
{
	char	*str;

	str = malloc(n + 1 * sizeof(char));
	if (str == NULL)
		return (0);
	ft_strlcpy(str, s1, n + 1);
	str[n] = '\0';
	return (str);
}


int	ft_search_space(char *str)
{
	while (*str)
	{
		if (*str <= 32 && *str >= 1)
			str ++;
		else
			return (0);
	}
	return (1);
}
