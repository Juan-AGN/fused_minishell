/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_functions2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 21:17:41 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/23 21:17:42 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exteroided.h"

int	first_forking(int *stdin, int *stdout, t_shell *shell, t_ret *pid_return)
{
	*stdin = dup(STDIN_FILENO);
	*stdout = dup(STDOUT_FILENO);
	if (*stdin == -1 || *stdout == -1)
	{
		perror("dup error");
		builtin_exit(NULL, shell, -1);
	}
	pid_return->return_value = redirect(shell, &(shell->token[0]),
			0, shell->ncomands);
	if (pid_return->return_value != 0)
	{
		close(*stdin);
		close(*stdout);
		pid_return->use_pid = 2;
		return (1);
	}
	if (e_ft_strncmp(shell->token[0].command, "exit", 4) == 0
		&& (shell->token[0].nparams == 0
			|| !is_numeric(shell->token[0].params[0])
			|| (shell->token[0].nparams == 1)))
	{
		close(*stdin);
		close(*stdout);
	}
	return (0);
}

t_ret	second_fork(int *stdin, int *stdout, t_shell *shell, t_ret *pid_return)
{
	if (dup2(*stdin, STDIN_FILENO) == -1
		|| dup2(*stdout, STDOUT_FILENO) == -1)
	{
		perror("dup error");
		close(*stdin);
		close(*stdout);
		builtin_exit(NULL, shell, -1);
	}
	close(*stdin);
	close(*stdout);
	pid_return->use_pid = 2;
	return (*pid_return);
}

void	handle_child(t_shell *shell, t_ret *pid_return, char **envp, int i)
{
	if (!shell->token[i].command)
	{
		pid_return->return_value
			= redirect(shell, &(shell->token[i]), i, shell->ncomands);
		builtin_exit(NULL, shell, pid_return->return_value);
	}
	pid_return->return_value
		= redirect(shell, &(shell->token[i]), i, shell->ncomands);
	if (pid_return->return_value != 0)
		builtin_exit(NULL, shell, pid_return->return_value);
	if (is_builtin(shell->token[i].command))
	{
		pid_return->return_value
			= exe_builtin(&(shell->token[i]), envp, shell->env, shell);
		builtin_exit(NULL, shell, pid_return->return_value);
	}
	if (!shell->directories)
	{
		perror("No path defined");
		builtin_exit(NULL, shell, 127);
	}
}

t_ret	loop_forking(t_shell *shell, char **envp, t_ret pid_return)
{
	int		i;
	char	*chain;

	i = 0;
	while (i < shell->ncomands)
	{
		pid_return.pid = fork();
		if (pid_return.pid == -1)
		{
			perror("fork error");
			builtin_exit(NULL, shell, -1);
		}
		if (pid_return.pid == 0)
		{
			handle_child(shell, &pid_return, envp, i);
			chain = token_to_str(&(shell->token[i]), shell);
			execute(chain, shell->directories, envp, shell);
		}
		i++;
	}
	return (pid_return);
}

t_ret	forking(t_shell *shell, char **envp)
{
	t_ret	pid_return;
	int		saved_stdin;
	int		saved_stdout;

	pid_return.pid = -1;
	pid_return.return_value = 0;
	pid_return.use_pid = 1;
	shell->directories = find_directories(envp, shell);
	if (shell->ncomands == 1 && shell->token[0].command != NULL
		&& is_builtin(shell->token[0].command))
	{
		if (first_forking(&saved_stdin, &saved_stdout, shell, &pid_return))
			return (pid_return);
		pid_return.return_value = exe_builtin(shell->token, envp,
				shell->env, shell);
		return (second_fork(&saved_stdin, &saved_stdout, shell, &pid_return));
	}
	return (loop_forking(shell, envp, pid_return));
}
