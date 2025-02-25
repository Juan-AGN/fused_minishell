/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:00:05 by juan-ant          #+#    #+#             */
/*   Updated: 2024/12/19 13:56:51 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	l1;
	unsigned int	l2;
	char			*ret;

	if (s1 != NULL)
		l1 = ft_strlen(s1);
	else
		l1 = 0;
	if (s2 != NULL)
		l2 = ft_strlen(s2);
	else
		l2 = 0;
	ret = malloc(1 + l1 + l2 * sizeof(char));
	if (ret == NULL)
		return (0);
	if (s1 != NULL)
	{
		ft_strlcpy(ret, s1, l1 + 1);
		ft_strlcat(ret, s2, l1 + l2 + 1);
	}
	else
		ft_strlcpy(ret, s2, l2 + 1);
	return (ret);
}
