/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:31:51 by juan-ant          #+#    #+#             */
/*   Updated: 2025/03/21 13:44:58 by juan-ant         ###   ########.fr       */
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
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("  ", 0);
		rl_redisplay();
	}
}

void	ft_handler_two(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
	}
	else if (signal == SIGQUIT)
	{
		printf("\n");
	}
}

void	ft_signal(void)
{
	struct sigaction	signal;

	signal.sa_handler = &ft_handler;
	signal.sa_flags = SA_RESTART;
	sigemptyset(&signal.sa_mask);
	sigaction(SIGINT, &signal, NULL);
	sigaction(SIGQUIT, &signal, NULL);
}

void	ft_disable_signal()
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &ft_handler_two);
	signal(SIGQUIT, &ft_handler_two);
}
