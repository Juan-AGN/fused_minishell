/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:13:39 by juan-ant          #+#    #+#             */
/*   Updated: 2024/08/03 12:36:47 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putprepbase(va_list args, int base)
{
	unsigned long	x;

	x = (unsigned long)va_arg(args, unsigned int);
	if (x <= 0)
		return (ft_prinstr("0", 0));
	else
		return (ft_priunbase((unsigned long)x, base, 1));
}

static int	ft_pformat(va_list args)
{
	int	n;

	n = ft_prinstr("0x", 2);
	if (n == -1)
		return (-1);
	return (n + ft_priunbase(va_arg(args, unsigned long), 39, 1));
}

static int	ft_value(const char *format, va_list args)
{
	format ++;
	if (*format == 'c')
		return (ft_prinstr(va_arg(args, char *), 1));
	else if (*format == '%')
		return (ft_prinstr("%", 0));
	else if (*format == 's')
		return (ft_prinstr(va_arg(args, char *), 0));
	else if (*format == 'i' || *format == 'd')
		return (ft_prinbr(va_arg(args, int), 1));
	else if (*format == 'X')
		return (ft_putprepbase(args, 7));
	else if (*format == 'x')
		return (ft_putprepbase(args, 39));
	else if (*format == 'p')
		return (ft_pformat(args));
	else if (*format == 'u')
		return (ft_putprepbase(args, 0));
	return (-1);
}

static int	ft_printer(const char *format, va_list args, int n)
{
	int	i;

	while (*format != '\0' && format != NULL)
	{
		i = n;
		if (*format == '%')
		{
			n = n + ft_value(format, args);
			format = format + 2;
		}
		else
		{
			if (write(1, format, 1) == -1)
				return (-1);
			n ++;
			format ++;
		}
		if (i > n)
			return (-1);
	}
	return (n);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		n;

	va_start(args, format);
	n = ft_printer(format, args, 0);
	va_end(args);
	return (n);
}
