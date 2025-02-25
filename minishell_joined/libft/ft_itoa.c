/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 13:15:43 by juan-ant          #+#    #+#             */
/*   Updated: 2023/10/01 14:23:48 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_nbr(char *aux, int n, int i)
{
	if (n == 0)
		aux[0] = '0';
	if (n < 0)
		aux[0] = '-';
	else
		n = n * -1;
	while (n != 0)
	{
		aux[i] = n % 10 * -1 + '0';
		n = n / 10;
		i --;
	}
}

char	*ft_itoa(int n)
{
	int		i;
	char	*aux;
	int		auxn;

	auxn = n;
	if (auxn < 0 || auxn == 0)
		i = 1;
	else
		i = 0;
	while (auxn != 0)
	{
		i ++;
		auxn = auxn / 10;
	}
	aux = ft_calloc(i + 1, sizeof(char));
	if (aux == NULL)
		return (0);
	ft_nbr(aux, n, i - 1);
	return (aux);
}
