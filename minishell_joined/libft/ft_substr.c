/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 17:09:30 by juan-ant          #+#    #+#             */
/*   Updated: 2023/09/23 18:56:48 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*str;
	unsigned int		l;

	l = ft_strlen(s);
	if (l <= start || len == 0)
		return (ft_calloc(1, sizeof(char)));
	if (l - start < len)
		len = l - start;
	str = ft_calloc(len + 1, sizeof(char));
	if (str == NULL)
		return (0);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}
