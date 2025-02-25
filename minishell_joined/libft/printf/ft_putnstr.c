/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 18:21:56 by juan-ant          #+#    #+#             */
/*   Updated: 2024/08/03 12:36:45 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_prinstr(char *str, int mode)
{
	int	n;

	n = 0;
	if (mode == 1)
	{
		if (write(1, &str, 1) == -1)
			return (-1);
		return (1);
	}
	else if (str == NULL)
		return (ft_prinstr("(null)", 0));
	while (*str != '\0')
	{
		if (write(1, str, 1) == -1)
			return (-1);
		n ++;
		str ++;
	}
	return (n);
}
