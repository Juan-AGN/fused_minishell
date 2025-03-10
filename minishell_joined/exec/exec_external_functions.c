#include "exteroided.h"

char **exec_convert_env_to_array(t_shell *shell)
{
    int count = 0;
    t_env *tmp = *(shell->env);
    
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }
    
    char **envp = (char **)malloc(sizeof(char *) * (count + 1));
    if (!envp)
        return NULL;
    
    tmp = *(shell->env);
    int i = 0;
    while (i < count)
    {
        size_t len = exec_ft_strlen(tmp->name) + exec_ft_strlen(tmp->content) + 2;
        envp[i] = (char *)malloc(len);
        if (!envp[i])
        {
            int j = i;
            while (--j >= 0)
                free(envp[j]);
            free(envp);
            return NULL;
        }
        envp[i][0] = '\0';
        exec_ft_strlcat(envp[i], tmp->name, len);
        exec_ft_strlcat(envp[i], "=", len);
        exec_ft_strlcat(envp[i], tmp->content, len);
        tmp = tmp->next;
        i++;
    }
    envp[count] = NULL;
    return envp;
}

void	exec_free_array(char **directories)
{
	int	i;

	i = 0;
	while (directories[i] != NULL)
	{
		free(directories[i]);
		i++;
	}
	free(directories);
}

void	create_pipes(int pipes[][2], int ncom)
{
	int	i;

	i = 0;
	while (i < ncom - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

char *token_to_str(const t_token *token)
{
    if (!token || !token->command)
        return NULL;

    size_t total_length = exec_ft_strlen(token->command);
    int i = 0;
    while (i < token->nparams)
    {
        total_length += 1; // Para el espacio
        total_length += exec_ft_strlen(token->params[i]);
        i++;
    }
    total_length += 1;
    char *result = (char *)malloc(total_length);
    if (!result)
        return NULL;
    result[0] = '\0';
    exec_ft_strlcat(result, token->command, total_length);
    i = 0;
    while (i < token->nparams)
    {
        exec_ft_strlcat(result, " ", total_length);
        exec_ft_strlcat(result, token->params[i], total_length);
        i++;
    }
    return result;
}

t_return	forking(int pipes[][2], t_shell *shell, char **directories, char **envp)
{
	int		i;
	pid_t	pid;
	char *chain;
	int return_status;
	t_return pid_return;

	i = 0;
	t_return.pid = -1;
	t_return.return_value = 0;
	t_return.use_pid = 1;
	while (i < shell->ncomands)
	{
		if (shell->ncomands == 1 && shell->token[0].command != NULL && is_builtin(shell->token[0].command))
		{
			pid_return.return_value = redirect(pipes, &(shell->token[0]), 0, shell->ncomands);
			if (pid_return.return_value != 0)
			{
				pid_return.use_pid = 2; // no hacer waitpid
				return (pid_return);
			}
			pid_return.return_value = execute_builtin(shell->token, envp ,shell->env);
			pid_return.use_pid = 2; // no hacer waitpid
				return (pid_return);
    	}
		t_return.pid = fork();
		if (t_return.pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (t_return.pid == 0)
		{
			if (!shell->token[i].command)
			{
				pid_return.return_value = redirect(pipes, &(shell->token[i]), i, shell->ncomands);
				if (pid_return.return_value != 0)
				{

				}
				exit(return_status);
			}
			else
			{
				chain = token_to_str(&(shell->token[i]));
				/*return_status = */redirect(pipes, &(shell->token[i]), i, shell->ncomands);
				if (is_builtin(shell->token[i].command)) //en builtins si hay dos errores se prioriza el de redirect
				{
					if (return_status == 0)
						return_status = execute_builtin(&(shell->token[i]), envp, shell->env);
					else
						execute_builtin(&(shell->token[i]), envp, shell->env);
					exit(return_status);
				}
				execute(chain, directories, envp);
			}
		}
		i++;
	}
	return (pid);
}

void	try(char *full_path, char **commands, char **directories, char **envp)
{
	if (access(full_path, X_OK) == 0)
	{
		execve(full_path, commands, envp);
		perror("execve error");
		free(full_path);
		free_array(commands);
		free_array(directories);
		exit(EXIT_FAILURE);
	}
	free(full_path);
}

char	**handle_params_allocation(char *command, char **directories)
{
	char	**commands;

	commands = exec_split(command, ' ');
	if (!commands)
	{
		perror("malloc error");
		free_array(directories);
		exit(EXIT_FAILURE);
	}
	return (commands);
}


/*
Se le pasa el comando entero junto a sus posibles parametros de ejecucion,
las rutas donde es posible que se encuentre y envp

*/
void	execute(char *command, char **directories, char **envp)
{
	char	**params;
	char	*full_path;
	int		i;

	params = handle_params_allocation(command, directories);
	i = 0;
	while (directories[i] != NULL)
	{
		full_path = build_full_path(directories[i], params[0]);
		if (!full_path)
		{
			free_array(params);
			free_array(directories);
			perror("malloc error");
			exit(EXIT_FAILURE);
		}
		try(full_path, params, directories, envp);
		i++;
	}
	free_array(params);
	free_array(directories);
	write(STDERR_FILENO, command, exec_ft_strlen(command));
	write(STDERR_FILENO, ": command not found\n", 20);
	exit(127);
}

char	**find_directories(char **envp)
{
	char	string_path[6];
	int		pos;
	char	**directories;
	char	*path_env;

	pos = 0;
	exec_ft_strlcpy(string_path, "PATH=", sizeof(string_path));
	while (envp[pos] != NULL)
	{
		if (exec_ft_strncmp(string_path, envp[pos], 5) == 0)
		{
			path_env = envp[pos] + 5;
			directories = exec_split(path_env, ':');
			if (!directories)
			{
				perror("malloc error");
				exit(EXIT_FAILURE);
			}
			return (directories);
		}
		pos++;
	}
	perror("No path defined");
	exit(EXIT_FAILURE);
}

char	*build_full_path(const char *directory, const char *command)
{
	size_t	total_size;
	char	*full_path;
	char	*cwd;

	// Si command ya es una ruta absoluta, se copia directamente
	if (command[0] == '/')
	{
		full_path = malloc(exec_ft_strlen(command) + 1);
		if (!full_path)
			return (NULL);
		exec_ft_strlcpy(full_path, command, exec_ft_strlen(command) + 1);
		return (full_path);
	}

	// Si es una ruta relativa con "./" o "../", convertirla a absoluta
	if (command[0] == '.' && (command[1] == '/' || command[1] == '.'))
	{
		cwd = getcwd(NULL, 0);  // getcwd asigna memoria automáticamente
		if (!cwd)
		{
			perror("getcwd");
			return (NULL);
		}
		total_size = exec_ft_strlen(cwd) + exec_ft_strlen(command) + 2;
		full_path = malloc(total_size);
		if (!full_path)
		{
			free(cwd);
			return (NULL);
		}
		exec_ft_strlcpy(full_path, cwd, total_size);
		exec_ft_strlcat(full_path, "/", total_size);
		exec_ft_strlcat(full_path, command, total_size);
		free(cwd);
		return (full_path);
	}
	total_size = exec_ft_strlen(directory) + exec_ft_strlen(command) + 2;
	full_path = malloc(total_size);
	if (!full_path)
		return (NULL);
	exec_ft_strlcpy(full_path, directory, total_size);
	exec_ft_strlcat(full_path, "/", total_size);
	exec_ft_strlcat(full_path, command, total_size);
	return (full_path);
}

int	returning(int ncom, pid_t pid)
{
	int	i;
	int	wpid;
	int	exit_code;
	int	status;

	i = 0;
	while (i < ncom)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid < 0)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (wpid == pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else
				exit_code = 1;
		}
		i++;
	}
	//exit(exit_code);
	return (exit_code);
}


void	here_doc_child(char *limiter, int fd)
{
	char	*line;
	size_t	limiter_len;

	limiter_len = exec_ft_strlen(limiter);
	while (1)
	{
		line = exec_get_next_line(0);
		if (!line)
			break ;
		if (exec_ft_strncmp(line, limiter, limiter_len) == 0
			&& line[limiter_len] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, exec_ft_strlen(line));
		free(line);
	}
	return;
}

