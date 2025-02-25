/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:56:17 by juan-ant          #+#    #+#             */
/*   Updated: 2023/09/23 17:07:42 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		n;
	char	*str;

	n = ft_strlen(s1);
	str = malloc(n + 1 * sizeof(char));
	if (str == NULL)
		return (0);
	ft_strlcpy(str, s1, n + 1);
	return (str);
}
