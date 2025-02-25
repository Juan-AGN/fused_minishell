/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:31:01 by juan-ant          #+#    #+#             */
/*   Updated: 2023/09/15 18:31:45 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	n;
	void	*a;

	a = b;
	n = 0;
	while (len != n)
	{
		*((unsigned char *)b) = c;
		b ++;
		n ++;
	}
	return (a);
}
