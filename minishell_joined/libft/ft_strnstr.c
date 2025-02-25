/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:19:03 by juan-ant          #+#    #+#             */
/*   Updated: 2023/09/18 19:50:27 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*aux;
	char	*aux2;
	size_t	len2;

	aux2 = (char *)needle;
	if (!*((char *)needle))
		return ((char *)haystack);
	while (len != 0 && *((char *)haystack))
	{
		len2 = len;
		aux = (char *)haystack;
		while (len2 != 0 && *((char *)haystack) == *((char *)needle))
		{
			haystack ++;
			needle ++;
			if (!*((char *)needle))
				return ((char *)aux);
			len2 --;
		}
		haystack = aux + 1;
		needle = aux2;
		len --;
	}
	return (NULL);
}
