/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:37:08 by juan-ant          #+#    #+#             */
/*   Updated: 2023/09/17 14:19:37 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*start;

	start = dst;
	if (!(char *)dst && !(char *)src)
		return (NULL);
	while (n != 0)
	{
		*((char *)dst) = *((char *)src);
		dst ++;
		src ++;
		n--;
	}
	return (start);
}
