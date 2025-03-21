/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juan-ant <juan-ant@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:16:58 by juan-ant          #+#    #+#             */
/*   Updated: 2025/03/21 17:47:55 by juan-ant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error_no_command(t_shell *minishell)
{
	if (minishell->error == -5 || minishell->token == NULL
		|| minishell->ncomands != 1)
		return ;
	if (minishell->token->command == NULL)
		return ;
	if (minishell->token->command[0] == '\0'
		&& minishell->token->infiles == NULL
		&& minishell->token->infiles == NULL
		&& minishell->token->params == NULL)
		ft_error_mini(minishell, 5, 0, 0);
}

void	ft_errors(t_shell *minishell)
{
	if (minishell->error == -5)
	{
		ft_free_for_exit(minishell);
		ft_printf("Malloc error\n");
		exit(-1);
	}
	if (minishell->error != 0)
	{
		if (minishell->error != 5)
			ft_printf("Quote error\n");
		minishell->error = 0;
	}
}

int	ft_cwd(t_shell *minishell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_free_for_exit(minishell);
		perror("getcwd() error");
		exit(-1);
	}
	minishell->cwd = ft_strjoin(cwd, "~$: ");
	if (minishell->cwd != NULL)
		minishell->input = readline(minishell->cwd);
	else
	{
		ft_free_for_exit(minishell);
		ft_printf("Malloc error\n");
		exit(-5);
	}
	free(cwd);
	return (0);
}

void	ft_handle_input(t_shell *minishell)
{
	int	ret;

	if (ft_search_space(minishell->input) == 0)
		add_history(minishell->input);
	else
		printf("");
	ret = ft_maintoken(minishell, minishell->input);
	if (ret == 0)
		ft_error_no_command(minishell);
	ft_disable_signal();
	if (minishell->input != NULL && ret == 0 && minishell->error == 0)
		handle_shell(minishell);
	ft_errors(minishell);
	ft_free_tokens(minishell, minishell->token);
	free(minishell->input);
	minishell->input = NULL;
	free(minishell->cwd);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*minishell;

	if (!envp[0])
		return (1);
	if (argc == -1 || argv == NULL)
		return (100);
	minishell = ft_prepare_values(envp);
	if (minishell == NULL)
		return (-5);
	rl_redisplay();
	while (1)
	{
		ft_signal();
		ft_cwd(minishell);
		if (minishell->input == NULL)
		{
			ft_free_for_exit(minishell);
			exit(0);
		}
		ft_handle_input(minishell);
	}
}
