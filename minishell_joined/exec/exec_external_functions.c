/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luialvar <luialvar@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:18:11 by luialvar          #+#    #+#             */
/*   Updated: 2025/03/13 11:18:13 by luialvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exteroided.h"

char	**exec_convert_env_to_array(t_shell *shell)
{
	int		count;
	t_env	*tmp;
	char	**envp;
	int		i;
	size_t	len;
	int		j;

	tmp = *(shell->env);
	count = 0;
	i = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	tmp = *(shell->env);
	while (i < count)
	{
		len = exec_ft_strlen(tmp->name) + exec_ft_strlen(tmp->content) + 2;
		envp[i] = (char *)malloc(len);
		if (!envp[i])
		{
			j = i;
			while (--j >= 0)
				free(envp[j]);
			free(envp);
			return (NULL);
		}
		envp[i][0] = '\0';
		exec_ft_strlcat(envp[i], tmp->name, len);
		exec_ft_strlcat(envp[i], "=", len);
		exec_ft_strlcat(envp[i], tmp->content, len);
		tmp = tmp->next;
		i++;
	}
	envp[count] = NULL;
	return (envp);
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

char	*token_to_str(const t_token *token)
{
	size_t	total_length;
	int		i;
	char	*result;

	if (!token || !token->command)
		return (NULL);
	total_length = exec_ft_strlen(token->command);
	i = 0;
	while (i < token->nparams)
	{
		total_length += 1;
		total_length += exec_ft_strlen(token->params[i]);
		i++;
	}
	total_length += 1;
	result = (char *)malloc(total_length);
	if (!result)
		return (NULL);
	result[0] = '\0';
	exec_ft_strlcat(result, token->command, total_length);
	i = 0;
	while (i < token->nparams)
	{
		exec_ft_strlcat(result, " ", total_length);
		exec_ft_strlcat(result, token->params[i], total_length);
		i++;
	}
	return (result);
}

t_ret	forking(int pipes[][2], t_shell *shell, char **direct, char **envp)
{
	int		i;
	char	*chain;
	t_ret	pid_return;
	int		saved_stdin;
	int		saved_stdout;

	i = 0;
	pid_return.pid = -1;
	pid_return.return_value = 0;
	pid_return.use_pid = 1;

	if (shell->ncomands == 1 && shell->token[0].command != NULL && is_builtin(shell->token[0].command))
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (saved_stdin == -1 || saved_stdout == -1)
		{
			perror("dup");
			pid_return.use_pid = 2;
			return (pid_return);
		}
		pid_return.return_value = redirect(pipes, &(shell->token[0]), 0, shell->ncomands);
		if (pid_return.return_value != 0)
		{
			pid_return.use_pid = 2;
			return (pid_return);
		}
		pid_return.return_value = execute_builtin(shell->token, envp, shell->env);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);

		pid_return.use_pid = 2;
		return (pid_return);
	}

	// === Comandos externos con fork ===
	while (i < shell->ncomands)
	{
		pid_return.pid = fork();
		if (pid_return.pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid_return.pid == 0) // Hijo
		{
			if (!shell->token[i].command)
			{
				pid_return.return_value = redirect(pipes, &(shell->token[i]), i, shell->ncomands);
				exit(pid_return.return_value);
			}
			else
			{
				chain = token_to_str(&(shell->token[i]));
				pid_return.return_value = redirect(pipes, &(shell->token[i]), i, shell->ncomands);
				if (pid_return.return_value != 0)
					exit(pid_return.return_value);
				if (is_builtin(shell->token[i].command))
				{
					pid_return.return_value = execute_builtin(&(shell->token[i]), envp, shell->env);
					exit(pid_return.return_value);
				}
				execute(chain, direct, envp);
			}
		}
		i++;
	}

	return (pid_return);
}

void	try(char *full_path, char **commands, char **directories, char **envp)
{
	struct	stat st;

	// Obtener información del archivo
	if (stat(full_path, &st) == 0)
	{
		// 1. Verificar si es un directorio
		if (S_ISDIR(st.st_mode))
		{
			write(STDERR_FILENO, full_path, exec_ft_strlen(full_path));
			write(STDERR_FILENO, ": Is a directory\n", 17);
			free(full_path);
			free_array(commands);
			free_array(directories);
			exit(126);
		}

		// 2. Verificar si tiene permisos de ejecución
		if (st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
		{
			// Intentar ejecutar el archivo
			execve(full_path, commands, envp);
			perror("execve error");
			free(full_path);
			free_array(commands);
			free_array(directories);
			exit(126);
		}

		// 3. Si no tiene permisos de ejecución, imprimir "Permission denied"
		write(STDERR_FILENO, full_path, exec_ft_strlen(full_path));
		write(STDERR_FILENO, ": Permission denied\n", 20);
		free(full_path);
		free_array(commands);
		free_array(directories);
		exit(126);
	}

	// Si no existe, simplemente liberamos la memoria y seguimos probando otras rutas.
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

	if (command[0] == '/')
	{
		full_path = malloc(exec_ft_strlen(command) + 1);
		if (!full_path)
			return (NULL);
		exec_ft_strlcpy(full_path, command, exec_ft_strlen(command) + 1);
		return (full_path);
	}

	if (command[0] == '.' && (command[1] == '/' || command[1] == '.'))
	{
		cwd = getcwd(NULL, 0);
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
	return ;
}
