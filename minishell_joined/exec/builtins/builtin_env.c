#include "builtins.h"

void	builtin_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		write(1, envp[i], ft_strrlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
}