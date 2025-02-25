/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:11:10 by juan-ant          #+#    #+#             */
/*   Updated: 2023/09/18 18:17:15 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n != 0)
	{
		if (*((unsigned char *)s1) != *((unsigned char *)s2))
		{
			return (*((unsigned char *)s1) - *((unsigned char *)s2));
		}
		s1 ++;
		s2 ++;
		n --;
	}
	return (0);
}
