#include "exteroided.h"

void	execute_builtin(t_token   *command/*, t_env **envp*/)
{
	if (ft_strrncmp(command->command, "echo\0", 5) == 0)
		builtin_echo(command->params);
    else if (ft_strrncmp(command->command, "cd\0", 3) == 0)
		builtin_cd(command->params);
    else if (ft_strrncmp(command->command, "pwd\0", 4) == 0)
		builtin_pwd();
	//else if (ft_strrncmp(command->command, "env\0", 4) == 0)
	//	builtin_env(envp);
	else if (ft_strrncmp(command->command, "exit\0", 5) == 0)
		builtin_exit(command->params);
	//else if (ft_strrncmp(command->command, "unset\0", 6) == 0)
	//	builtin_unset(command->params, envp);
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



void	run(t_shell *shell, char **directories, char **envp)
{
	int		(*pipes)[2];
	pid_t	pid;
	int		i;

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
	returning(shell->ncomands, pid);
}

void    handle_shell(t_shell *shell) 
{
    char	**directories;
    char **envp;

    if (shell->ncomands == 0)
        return;
    envp = convert_env_to_array(shell);
    if (!envp)
    {
        perror("malloc error");
        return
    }
    if (shell->ncomands == 1 && is_builtin(shell->token[0].command))
    {
        execute_builtin(shell->token /*,shell->env*/);
        free_array(envp);
        return;
    }
	directories = find_directories(envp);
	if (!directories)
	{
        free_array(envp);
		perror("malloc error");
		return
	}
	run(shell, directories, envp);
}
