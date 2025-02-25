/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:24:46 by juan-ant          #+#    #+#             */
/*   Updated: 2023/09/17 15:03:27 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	n;

	n = ft_strlen(dst);
	if (n > dstsize)
		return (dstsize + ft_strlen(src));
	dst = dst + n;
	return (n + ft_strlcpy(dst, src, dstsize - n));
}
