#include "builtins.h"

int	builtin_env(int nparams, char **envp)
{
	int	i;

	i = 0;
	if (nparams != 0)
		return 127;
	while (envp[i])
	{
		write(1, envp[i], ft_strrlen(envp[i]));
		write(1, "\n", 1);
		i++;
	}
	return 0;
}