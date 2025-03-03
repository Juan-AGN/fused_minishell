#include "exteroided.h"

void	execute_builtin(t_token   *command, char ** envp, t_env **env)
{
	if (ft_strrncmp(command->command, "echo\0", 5) == 0)
		builtin_echo(command->params);
    else if (ft_strrncmp(command->command, "cd\0", 3) == 0)
		builtin_cd(command->params);
    else if (ft_strrncmp(command->command, "pwd\0", 4) == 0)
		builtin_pwd();
	else if (ft_strrncmp(command->command, "env\0", 4) == 0)
		builtin_env(envp);
	else if (ft_strrncmp(command->command, "exit\0", 5) == 0)
		builtin_exit(command->params);
	else if (ft_strrncmp(command->command, "unset\0", 6) == 0)
		builtin_unset(command, env);
	//else if (ft_strrncmp(command->command, "export\0", 7) == 0)
	//	builtin_export(command->params, envp);
        return;
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

/*
create pipes, eso lo primero
hasta aqui es facil, ahora solo hay que cambiar el redirect,
es importante pensar que en el redirect hay que ir pasando token a token
la estructura de run se quedaria muy parecida
lo importante ahora es pensar en la implementacion del redirect, y pensar
que hay que cambiar el handle_tofile y handle_fromfile


*/

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
			perror("error file");
		}
		free(chain);
		i++;
	}
	if (shit != i)
	{
		dup2(fileout, STDOUT_FILENO);
		close(fileout);
		if (current < ncomands - 1) //la clave a ver
			close(pipes[current][1]);
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
	while (i < token->ninfiles)
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

void	redirect(int pipes[][2], t_token *token, int current, int ncomands)
{
	int	i;

	i = 0;
	handle_fromfile(pipes, token, current);
	handle_tofile(pipes, token, current, ncomands);
	while (i < ncomands - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	run(t_shell *shell, char **directories, char **envp)
{
	int		(*pipes)[2];
	pid_t	pid;
	int		i;
	int		exit_code;

	pipes = malloc(sizeof(int [2]) * (shell->ncomands - 1));
	if (!pipes)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	i = 0;
	create_pipes(pipes, shell->ncomands);
	pid = forking(pipes, shell, directories, envp);
	free_array(directories);
    free_array(envp);
	while (i < shell->ncomands - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	free(pipes);
	free(shell->exit_code);
	exit_code = returning(shell->ncomands, pid);
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
	if (shell->ncomands == 1 && shell->token[0].command != NULL && is_builtin(shell->token[0].command))
	{
        execute_builtin(shell->token, envp ,shell->env);
        free_array(envp);
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
