/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:25:31 by juan-ant          #+#    #+#             */
/*   Updated: 2023/09/17 14:17:50 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*start;

	start = dst;
	if (!(char *)dst && !(char *)src)
		return (NULL);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		dst = dst + len - 1;
		src = src + len - 1;
		while (len != 0)
		{
			*((char *)dst) = *((char *)src);
			src --;
			dst --;
			len --;
		}
	}
	return (start);
}
