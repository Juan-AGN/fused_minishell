/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 14:57:06 by juan-ant          #+#    #+#             */
/*   Updated: 2023/10/01 15:17:30 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*aux;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s) + 1;
	aux = ft_calloc(len, sizeof(char));
	if (aux == NULL)
		return (0);
	while (s[i] != '\0')
	{
		aux[i] = f(i, s[i]);
		i ++;
	}
	return (aux);
}
