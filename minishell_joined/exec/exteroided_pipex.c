/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exteroided_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:19:09 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/13 11:19:10 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exteroided.h"

int	redirect(t_shell *shell, t_token *token, int current, int ncomands)
{
	int	i;
	int	read_heredoc;
	int	exit_value;
	int	current_ncomands[2];

	i = 0;
	read_heredoc = open_heredocs(token, shell);
	current_ncomands[0] = current;
	current_ncomands[1] = ncomands;
	exit_value = han_red(shell, token, current_ncomands, read_heredoc);
	while (i < ncomands - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
	return (exit_value);
}

void	rest_of_run(t_ret *pid_return, t_shell *shell, int *exit_code)
{
	if (pid_return->use_pid == 2)
	{
		free(shell->exit_code);
		*exit_code = pid_return->return_value;
		shell->exit_code = ft_itoa(*exit_code);
		if (!shell->exit_code)
		{
			perror("malloc error");
			builtin_exit(NULL, shell, -1);
		}
		return ;
	}
	free(shell->exit_code);
	*exit_code = returning(shell->ncomands, pid_return->pid, shell);
	shell->exit_code = ft_itoa(*exit_code);
	if (!shell->exit_code)
	{
		perror("malloc error");
		builtin_exit(NULL, shell, -1);
	}
}

void	run(t_shell *shell, char **envp)
{
	int		i;
	int		exit_code;
	t_ret	pid_return;

	shell->pipes = malloc(sizeof(int [2]) * (shell->ncomands - 1));
	if (!shell->pipes)
	{
		perror("malloc error");
		builtin_exit(NULL, shell, -1);
	}
	i = 0;
	create_pipes(shell->pipes, shell->ncomands, shell);
	pid_return = forking(shell, envp);
	if (shell->directories != NULL)
		free_array(shell->directories);
	free_array(envp);
	while (i < shell->ncomands - 1)
	{
		close(shell->pipes[i][0]);
		close(shell->pipes[i][1]);
		i++;
	}
	free(shell->pipes);
	rest_of_run(&pid_return, shell, &exit_code);
}

void	handle_shell(t_shell *shell)
{
	shell->envp = exec_convert_env_to_array(shell);
	if (!shell->envp)
	{
		perror("malloc error");
		builtin_exit(NULL, shell, -1);
	}
	run(shell, shell->envp);
}

void	exec_free_all(t_shell *shell)
{
	if (shell->pipes != NULL)
		free(shell->pipes);
	if (shell->envp != NULL)
		free_array(shell->envp);
	if (shell->directories != NULL)
		free_array(shell->directories);
	ft_free_for_exit(shell);
}
