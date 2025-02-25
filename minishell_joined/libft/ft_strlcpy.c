/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:31:57 by juan-ant          #+#    #+#             */
/*   Updated: 2023/09/16 18:01:56 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	n;

	n = 0;
	while (*src)
	{
		n ++;
		src ++;
	}
	src = src - n;
	if (dstsize == 0)
		return (n);
	while (dstsize != 1 && *src)
	{
		*dst = *src;
		dst ++;
		src ++;
		dstsize --;
	}
	*dst = '\0';
	return (n);
}
