/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exteroided_pipex2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 22:25:50 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/23 22:25:57 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exteroided.h"

int	exe_builtin(t_token *command, char **envp, t_env **env, t_shell *shell)
{
	int	return_status;

	return_status = 0;
	if (ft_strrncmp(command->command, "echo\0", 5) == 0)
		builtin_echo(command);
	else if (ft_strrncmp(command->command, "cd\0", 3) == 0)
		return_status = builtin_cd(command->params, env, shell,
				command->nparams);
	else if (ft_strrncmp(command->command, "pwd\0", 4) == 0)
		builtin_pwd(shell);
	else if (ft_strrncmp(command->command, "env\0", 4) == 0)
		return_status = builtin_env(command->nparams, envp);
	else if (ft_strrncmp(command->command, "exit\0", 5) == 0)
		return_status = builtin_exit(command, shell, -1);
	else if (ft_strrncmp(command->command, "unset\0", 6) == 0)
		builtin_unset(command, env);
	else if (ft_strrncmp(command->command, "export\0", 7) == 0)
		return_status = builtin_export(command, env, shell);
	shell->cd_checker = -1;
	return (return_status);
}

int	is_builtin(char *builtin)
{
	if (ft_strrncmp(builtin, "echo\0", 5) == 0
		|| ft_strrncmp(builtin, "cd\0", 3) == 0
		|| ft_strrncmp(builtin, "pwd\0", 4) == 0
		|| ft_strrncmp(builtin, "env\0", 4) == 0
		|| ft_strrncmp(builtin, "exit\0", 5) == 0
		|| ft_strrncmp(builtin, "unset\0", 6) == 0
		|| ft_strrncmp(builtin, "export\0", 7) == 0)
		return (1);
	return (0);
}

void	process_heredoc_entry(char *entry, int *pipe_fd, t_shell *shell)
{
	char	*chain;

	if (e_ft_strncmp(entry, "<<", 2) == 0)
	{
		chain = exec_ft_substr(entry, 3, exec_ft_strlen(entry) - 3);
		if (pipe(pipe_fd) < 0)
		{
			perror("Error creating heredoc pipe");
			free(chain);
			builtin_exit(NULL, shell, -1);
		}
		signal(SIGINT, SIG_DFL);
		here_doc_child(chain, pipe_fd[1]);
		ft_disable_signal();
		close(pipe_fd[1]);
		free(chain);
	}
	else if (e_ft_strncmp(entry, "< ", 2) == 0)
		pipe_fd[0] = -1;
}

int	open_heredocs(t_token *token, t_shell *shell)
{
	int	i;
	int	pipe_fd[2];

	i = 0;
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	while (i < token->ninout)
	{
		process_heredoc_entry(token->inout[i], pipe_fd, shell);
		i++;
	}
	return (pipe_fd[0]);
}

void	first_han(t_token *token, int current_ncomands[2], t_shell *shell)
{
	if (token->ninfiles == 0 && current_ncomands[0] > 0)
		dup2(shell->pipes[current_ncomands[0] - 1][0], STDIN_FILENO);
	if (token->noutfiles == 0 && current_ncomands[0] < current_ncomands[1] - 1)
		dup2(shell->pipes[current_ncomands[0]][1], STDOUT_FILENO);
}
