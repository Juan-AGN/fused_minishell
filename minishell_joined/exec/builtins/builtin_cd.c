#include "builtins.h"

void	builtin_cd(char **args)
{
	char	*path;

	if (!args[0]) // Si no se pasa argumento, cambiar a $HOME
	{
		path = getenv("HOME"); // Obtener el valor de la variable de entorno HOME
		if (!path)
		{
			write(2, "cd: HOME not set\n", 17);
			return ;
		}
	}
	else
		path = args[0];
	if (chdir(path) == -1)
		perror("cd");
}