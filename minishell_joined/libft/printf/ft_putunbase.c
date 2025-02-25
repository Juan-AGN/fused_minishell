/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:39:32 by juan-ant          #+#    #+#             */
/*   Updated: 2024/08/03 12:36:43 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_priunbase(unsigned long num, int diff, int start)
{
	unsigned long	base;
	int				n;

	n = 0;
	if (diff != 0)
		base = 16;
	else
		base = 10;
	if (num > 0 || start == 1)
	{
		n = ft_priunbase(num / base, diff, 0);
		if (n == -1)
			return (-1);
		n = n + 1;
		if (num % base >= 10)
			num = num % base + '0' + diff;
		else
			num = num % base + '0';
		if (write(1, &num, 1) == -1)
			return (-1);
	}
	return (n);
}
