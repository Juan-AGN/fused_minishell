/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 13:11:10 by juan-ant          #+#    #+#             */
/*   Updated: 2023/09/16 19:14:36 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n != 0 && *s1 && *s2)
	{
		if (*s1 != *s2)
		{
			return (((unsigned char)*s1) - ((unsigned char)*s2));
		}
		s1 ++;
		s2 ++;
		n --;
	}
	if (n == 0)
		return (0);
	return (((unsigned char)*s1) - ((unsigned char)*s2));
}
