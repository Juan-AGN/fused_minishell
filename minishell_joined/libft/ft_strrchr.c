/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 16:26:50 by juan-ant          #+#    #+#             */
/*   Updated: 2023/09/17 17:09:46 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ch;

	ch = NULL;
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			ch = (char *)s;
		s ++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (ch);
}
