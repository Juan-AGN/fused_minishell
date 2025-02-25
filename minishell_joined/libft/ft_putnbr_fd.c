/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 17:08:34 by juan-ant          #+#    #+#             */
/*   Updated: 2023/10/01 17:13:59 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int	i;
	int	aux[11];

	i = 0;
	if (n == 0)
		write (fd, "0", 1);
	if (n < 0)
		write(fd, "-", 1);
	while (n != 0)
	{
		if (n > 0)
			aux[i] = n % 10 + '0';
		else
			aux[i] = n % 10 * -1 + '0';
		n = n / 10;
		i ++;
	}
	i --;
	while (i > -1)
	{
		write(fd, &aux[i], 1);
		i --;
	}
}
