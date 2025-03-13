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

int	execute_builtin(t_token   *command, char ** envp, t_env **env)
{
	int return_status = 0; 

	if (ft_strrncmp(command->command, "echo\0", 5) == 0)
		builtin_echo(command);
    else if (ft_strrncmp(command->command, "cd\0", 3) == 0)
		return_status = builtin_cd(command->params);
    else if (ft_strrncmp(command->command, "pwd\0", 4) == 0)
		builtin_pwd();
	else if (ft_strrncmp(command->command, "env\0", 4) == 0)
		return_status = builtin_env(command->nparams, envp);
	else if (ft_strrncmp(command->command, "exit\0", 5) == 0)
		return_status = builtin_exit(command->params);
	else if (ft_strrncmp(command->command, "unset\0", 6) == 0)
		builtin_unset(command, env);
	else if (ft_strrncmp(command->command, "export\0", 7) == 0)
		return_status= builtin_export(command, env);
        return (return_status);
}

int is_builtin(char *builtin)
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

int	open_heredocs(t_token *token)
{
	int i = 0;
	char *chain;
	int		pipe_heredoc[2];

	pipe_heredoc[0] = -1;
	pipe_heredoc[1] = -1;
	while (i < token->ninout) //primero habria que hacer todos los heredocs y luego los otros
	{
		chain = exec_ft_substr(token->inout[i], 3, exec_ft_strlen(token->inout[i]) - 3);
		if ((exec_ft_strncmp(token->inout[i], "<<", 2)) == 0)
		{
			if (pipe(pipe_heredoc) < 0)
            {
                perror("Error creating heredoc pipe");
                exit(EXIT_FAILURE); // hay que mirar estas cosas para que cierre la shell
            }
			here_doc_child(chain, pipe_heredoc[1]);
			close(pipe_heredoc[1]);
		}
		if ((exec_ft_strncmp(token->inout[i], "< ", 2)) == 0)
			pipe_heredoc[0] = -1;
		free(chain);
		i++;
	}
	return (pipe_heredoc[0]); // se devuelve el extremo de lectura
}

int	handle_redirections(int pipes[][2], t_token *token, int current, int ncomands, int real_heredoc)
{
	int i;
	int	fileout;
	int filein;
	char *chain;

	i = 0;
	fileout = 0;
	filein = -1;
	if (token->ninfiles == 0 && current > 0)
		dup2(pipes[current - 1][0], STDIN_FILENO);
	if (token->noutfiles == 0 && current < ncomands - 1)
		dup2(pipes[current][1], STDOUT_FILENO);
	while (i < token->ninout)
	{
		chain = exec_ft_substr(token->inout[i], 3, exec_ft_strlen(token->inout[i]) - 3);
		if ((exec_ft_strncmp(token->inout[i], ">>", 2)) == 0)
			fileout = open(chain, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		else if (exec_ft_strncmp(token->inout[i], "> ", 2) == 0)
			fileout = open(chain, O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		if (fileout < 0)
		{
			perror("error file");
			return 1;
		}
		if ((exec_ft_strncmp(token->inout[i], "< ", 2)) == 0)
		{
			filein = open(chain, O_RDONLY);
			if (filein < 0)
			{
				perror("error file");
				return 1;
			}
		}
		free(chain);
		i++;
	}
	if (real_heredoc > -1 && token->ninfiles > 0)
	{
		dup2(real_heredoc, STDIN_FILENO);
		close(real_heredoc); 
	}
	else if (real_heredoc == -1 && token->ninfiles > 0)
	{
		dup2(filein, STDIN_FILENO);
		close(filein);
	}
	if (token->noutfiles > 0)
	{
	dup2(fileout, STDOUT_FILENO);
	close(fileout);
	}
	return 0;
}

int	redirect(int pipes[][2], t_token *token, int current, int ncomands)
{
	int	i;
	int read_heredoc;
	int exit_value;

	i = 0;
	read_heredoc = open_heredocs(token);
	exit_value = handle_redirections(pipes, token, current, ncomands, read_heredoc);
	/*handle_fromfile(pipes, token, current);
	handle_tofile(pipes, token, current, ncomands);*/
	while (i < ncomands - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	return (exit_value);
}

/*
void	handle_tofile(int pipes[][2], t_token *token, int current, int ncomands)
{
	int i;
	int	fileout;
	int shit;
	char *chain;

	fileout = -1;
	i = 0;
	shit = -1;
	if (token->noutfiles == 0 && current < ncomands - 1)
		dup2(pipes[current][1], STDOUT_FILENO);
	while (i < token->noutfiles)
	{
		chain = exec_ft_substr(token->outfiles[i], 3, exec_ft_strlen(token->outfiles[i]) - 3);
		if ((exec_ft_strncmp(token->outfiles[i], ">>", 2)) == 0)
			fileout = open(chain, O_WRONLY | O_CREAT
					| O_APPEND, 0644);
		else
			fileout = open(chain, O_WRONLY | O_CREAT
					| O_TRUNC, 0644);
		if (fileout < 0)
		{
			shit = i;
			perror("error file"); //y si se escrie a un archivo sin permisos, hay que verlo?
		}
		free(chain);
		i++;
	}
	if (shit != i)
	{
		dup2(fileout, STDOUT_FILENO);
		close(fileout);
	}
}

void	handle_fromfile(int pipes[][2], t_token *token, int current)
{
	int i;
	int		pipefd[2];
	int		filein;
	int		shit;
	char *chain;
	int		pipe_heredoc[2];

	filein = -1;
	i = 0;
	shit = -1;
	if (token->ninfiles == 0 && current > 0)
		dup2(pipes[current - 1][0], STDIN_FILENO);
	while (i < token->ninfiles) //primero habria que hacer todos los heredocs y luego los otros
	{
		chain = exec_ft_substr(token->infiles[i], 3, exec_ft_strlen(token->infiles[i]) - 3);
		if ((exec_ft_strncmp(token->infiles[i], "<<", 2)) != 0)
		{
			filein = open(chain, O_RDONLY);
			if (filein < 0)
			{
				perror("error file");
				shit = 1;
			}
			else
				shit = 0;
		}
		else
		{
			if (pipe(pipe_heredoc) < 0)
            {
                perror("Error creating heredoc pipe");
                exit(EXIT_FAILURE);
            }
			shit = 2;
			here_doc_child(chain, pipe_heredoc[1]);
			close(pipe_heredoc[1]);
		}
		free(chain);
		i++;
	}
	if (shit == 1)
	{
		if (pipe(pipefd) < 0)
		{
			perror("Error creating pipe");
			exit(EXIT_FAILURE);
		}
		close(pipefd[1]);
		filein = pipefd[0];
		dup2(filein, STDIN_FILENO);
		close(filein);
	}
	else if (shit == 0)
	{
		dup2(filein, STDIN_FILENO);
		close(filein);
	}
	else if (shit == 2)
	{
		dup2(pipe_heredoc[0], STDIN_FILENO);
		close(pipe_heredoc[0]); 
	}
}
*/

void	run(t_shell *shell, char **directories, char **envp)
{
	int		(*pipes)[2];
	int		i;
	int		exit_code;
	t_return pid_return;

	pipes = malloc(sizeof(int [2]) * (shell->ncomands - 1)); // ver el caso en que ncomands es 1 porque puede que no libere memoria abajo, ver si asignando a null sigue funcionando
	if (!pipes)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	create_pipes(pipes, shell->ncomands);
	pid_return = forking(pipes, shell, directories, envp);
	free_array(directories);
    free_array(envp);
	if (pid_return.use_pid == 2)
	{
		free(shell->exit_code);
		exit_code = pid_return.return_value;
		shell->exit_code = ft_itoa(exit_code);
		if (!shell->exit_code)
		{
			perror("malloc error");
			return;
		}
		return;
	}
	while (i < shell->ncomands - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	free(pipes);
	free(shell->exit_code);
	exit_code = returning(shell->ncomands, pid_return.pid);
	shell->exit_code = ft_itoa(exit_code);
	if (!shell->exit_code)
	{
        perror("malloc error");
        return;
    }
}

void    handle_shell(t_shell *shell) 
{
    char	**directories;
    char **envp;

    if (shell->ncomands == 0)
        return;
    envp = exec_convert_env_to_array(shell);
    if (!envp)
    {
        perror("malloc error");
        return;
    }
	directories = find_directories(envp);
	if (!directories)
	{
        free_array(envp);
		perror("malloc error");
		return;
	}
	run(shell, directories, envp);
}
