/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:39:32 by juan-ant          #+#    #+#             */
/*   Updated: 2024/08/03 12:36:46 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_writer(int num)
{
	int	n;

	n = ft_prinbr(num / 10, 0);
	if (n == -1)
		return (-1);
	if (num >= 0)
		num = num % 10 + '0';
	else
		num = num % 10 * -1 + '0';
	if (write(1, &num, 1) == -1)
		return (-1);
	n = n + 1;
	return (n);
}

int	ft_prinbr(int num, int start)
{
	int	n;

	if (num < 0 && start == 1)
		if (write(1, "-", 1) == -1)
			return (-1);
	n = 0;
	if (num != 0 || start == 1)
	{
		n = ft_writer(num);
		if (n == -1)
			return (-1);
	}
	if (start == 1 && num < 0)
		return (n + 1);
	return (n);
}
