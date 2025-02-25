/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 19:31:59 by juan-ant          #+#    #+#             */
/*   Updated: 2023/09/27 19:28:19 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*finish;
	char	*start;

	if ((!*s1 && !*set) || !*s1)
		return (ft_calloc(1, sizeof(char)));
	finish = (char *)s1 + ft_strlen(s1);
	while (*s1 && ft_strchr(set, *s1) != NULL)
		s1 ++;
	start = (char *)s1;
	s1 = s1 + ft_strlen(s1) - 1;
	while (*s1 && ft_strchr(set, *s1) != NULL)
		s1 --;
	finish = (char *)s1 + 1;
	if (finish > start)
		return (ft_substr(start, 0, ft_strlen(start) - ft_strlen(finish)));
	else
		return (ft_substr(start, 0, ft_strlen(start)));
}
