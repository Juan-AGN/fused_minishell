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
        size_t len = strlen(tmp->name) + strlen(tmp->content) + 2;
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
        ft_strllcat(envp[i], tmp->name, len);
        ft_strllcat(envp[i], "=", len);
        ft_strllcat(envp[i], tmp->content, len);
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

size_t	exec_ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	while (dst[len] && len < size)
		len++;
	while (src[i] && (len + i + 1) < size)
	{
		dst[len + i] = src[i];
		i++;
	}
	if (len < size)
		dst[len + i] = '\0';
	return (len + ft_strlen(src));
}

size_t	exec_ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	exec_create_pipes(int pipes[][2], int ncom)
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

pid_t	forking(int pipes[][2], t_shell *shell, char **directories, char **envp)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i < shell->ncomands)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			redirect(pipes, ncom_ishere, i, argv);
			execute(argv[i + 2], directories, envp);
		}
		i++;
	}
	return (pid);
}
