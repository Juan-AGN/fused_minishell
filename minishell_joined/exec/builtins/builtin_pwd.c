#include "builtins.h"

void	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0); // Solicita memoria dinámica para almacenar el directorio actual
	if (cwd != NULL)
	{
		write(1, cwd, ft_strrlen(cwd));
		write(1, "\n", 1);
		free(cwd);
	}
	else
		perror("pwd");
}