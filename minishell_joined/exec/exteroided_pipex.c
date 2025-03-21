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

	if (exec_ft_strncmp(entry, "<<", 2) == 0)
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
	else if (exec_ft_strncmp(entry, "< ", 2) == 0)
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

int	han_red(t_shell *shell, t_token *token, int current_ncomands[2], int real)
{
	int		i;
	int		fileout;
	int		filein;
	char	*chain;

	i = 0;
	fileout = 0;
	filein = -1;
	if (token->ninfiles == 0 && current_ncomands[0] > 0)
		dup2(shell->pipes[current_ncomands[0] - 1][0], STDIN_FILENO);
	if (token->noutfiles == 0 && current_ncomands[0] < current_ncomands[1] - 1)
		dup2(shell->pipes[current_ncomands[0]][1], STDOUT_FILENO);
	while (i < token->ninout)
	{
		chain = exec_ft_substr(token->inout[i], 3,
				exec_ft_strlen(token->inout[i]) - 3);
		if ((exec_ft_strncmp(token->inout[i], ">>", 2)) == 0)
			fileout = open(chain, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		else if (exec_ft_strncmp(token->inout[i], "> ", 2) == 0)
			fileout = open(chain, O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		if (fileout < 0)
		{
			free(chain);
			perror("error file");
			if (filein >= 0)
				close(filein);
			return (1);
		}
		if ((exec_ft_strncmp(token->inout[i], "< ", 2)) == 0)
		{
			filein = open(chain, O_RDONLY);
			if (filein < 0)
			{
				free(chain);
				perror("error file");
				if (fileout > 0)
					close(fileout);
				return (1);
			}
		}
		free(chain);
		i++;
	}
	if (real > -1 && token->ninfiles > 0)
	{
		if (dup2(real, STDIN_FILENO) == -1)
		{
			perror("dup2 heredoc error");
			close(real);
			builtin_exit(NULL, shell, -1);
		}
		close(real);
	}
	else if (real == -1 && token->ninfiles > 0)
	{
		if (dup2(filein, STDIN_FILENO) == -1)
		{
			perror("dup2 filein error");
			if (filein >= 0)
				close(filein);
			builtin_exit(NULL, shell, -1);
		}
		close(filein);
	}
	if (token->noutfiles > 0)
	{
		if (dup2(fileout, STDOUT_FILENO) == -1)
		{
			perror("dup2 fileout error");
			if (fileout > 0)
				close(fileout);
			builtin_exit(NULL, shell, -1);
		}
		close(fileout);
	}
	if (filein >= 0)
		close(filein);
	if (fileout > 0)
		close(fileout);
	return (0);
}

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
