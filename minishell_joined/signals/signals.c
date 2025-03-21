/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:31:51 by juan-ant          #+#    #+#             */
/*   Updated: 2025/03/21 18:41:23 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  ", 1);
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_handler_two(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
	}
}

void	sigquit_handler(int signal)
{
	signal = 0;
}

void	ft_signal(void)
{
	signal(SIGINT, &ft_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_disable_signal(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ft_handler_two);
	signal(SIGQUIT, &sigquit_handler);
}
